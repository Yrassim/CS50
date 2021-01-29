import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # How much cash the user currently has
    select = db.execute("SELECT cash from users where id = :id", id = session["user_id"])
    cash = select[0]["cash"]

    rows=db.execute("SELECT symbol, SUM(shares) FROM purchases WHERE user_id = :user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=session["user_id"])

    dic = [] # where to save the data reteive from database
    all_total = 0
    for row in rows:
        auction = lookup(row["symbol"])
        dic.append({"symbol": auction["symbol"], "name": auction['name'], "shares":row['SUM(shares)'], "price":auction['price'], "total":usd(row['SUM(shares)'] * auction['price'])})

        all_total += (row['SUM(shares)'] * auction['price'])
    all_total += cash
    return render_template("index.html", dic=dic, all_total = usd(all_total), cash=usd(cash))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("You must provide a symbol.", 400)
        shares = int(request.form.get("shares"))
        if not shares:
            return apology("You must provide number of shares.", 400)
        if lookup(symbol) is None:
            return apology("The symbol is incorrect or does not exist")

        # get share price and the total purchased
        sharePrice = int(lookup(symbol)['price'])
        total = sharePrice * shares
        # How much cash the user currently has
        row = db.execute("SELECT cash from users where id = :id", id = session["user_id"])
        cash = row[0]["cash"]
        #Compare if there are enough to buy shares
        if cash < total:
            return apology("You don't have enough to buy these numbres of share")
        else:
            newCash = cash - total
            db.execute("UPDATE users SET cash = :newCash where id = :id", newCash = newCash, id = session["user_id"])
            db.execute("INSERT INTO purchases (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=symbol, shares=shares, price=sharePrice)

            flash("Bought!") # Output the string. Provided by flask
            return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT symbol, shares, price, time from purchases where user_id = :user_id", user_id = session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("You must provide a symbol.", 400)
        else:
            stock = lookup(symbol)
            return render_template("quoted.html", stock=stock)

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        if not username:
            return apology("You must provide a Username.", 403)

        password = request.form.get("password")
        if not password:
            return apology("You must provide a password.", 403)

        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("You must provide a Password (again).", 403)
        elif password != confirmation:
            return apology("your two passwords do not match", 403)
        password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=password)
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        rows = db.execute("SELECT symbol FROM purchases WHERE user_id = :user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=session["user_id"])
        symbol_dic=[]
        for row in rows:
            symbol_dic.append(row["symbol"])
        return render_template("sell.html", symbol_dic=symbol_dic)
    else:
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("You must provide a symbol.", 400)
        shares = int(request.form.get("shares"))
        if not shares:
            return apology("You must provide number of shares.", 400)
        if lookup(symbol) is None:
            return apology("The symbol is incorrect or does not exist")
        # get share price and the total purchased
        sharePrice = int(lookup(symbol)['price'])
        total = sharePrice * shares

        rows = db.execute("SELECT symbol, SUM(shares) FROM purchases WHERE user_id = :user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=session["user_id"])
        for row in rows:
            if symbol == row["symbol"]:
                if shares > row["SUM(shares)"]:
                    return apology("You do not have that much of shares", 400)
        # How much cash the user currently has
        row=db.execute("SELECT cash from users where id = :id", id = session["user_id"])
        cash = row[0]["cash"]

        newCash = cash + total
        db.execute("UPDATE users SET cash = :newCash where id = :id", newCash = newCash, id = session["user_id"])
        db.execute("INSERT INTO purchases (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=symbol, shares=-1*shares, price=sharePrice)

        flash("Sold!") # Output the string. Provided by flask
        return redirect("/")

@app.route("/change_password", methods=["GET", "POST"])
@login_required
def preferences():

    if request.method == "GET":
        return render_template("change_password.html")
    else:
        password = request.form.get("current_password")
        if not password:
            return apology("You must provide a password.", 403)
        new_password = request.form.get("new_password")
        if not new_password:
            return apology("You must provide a new password.", 403)
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("You must confirm the new password.", 403)

        # select the hash of the old password to compare
        select = db.execute("SELECT hash from users where id = :id", id = session["user_id"])
        old_passwordHash = select[0]["hash"]

        if not check_password_hash(old_passwordHash, password):
            return apology("invalid current password", 403)
        elif new_password != confirmation:
            return apology("The new password and the confiramtion do not match, please check", 403)
        else:
            new_password = generate_password_hash(new_password)
            db.execute("UPDATE users SET hash = :new_password where id = :id", new_password = new_password, id = session["user_id"])
            flash("Password Updated!") # Output the string. Provided by flask
            return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
