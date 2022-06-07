import flask
import psycopg2
from flask import Flask, render_template, request

app = Flask(__name__)
connect = psycopg2.connect("dbname=postgres user=postgres password=1111")
cur = connect.cursor()  # create cursor


def login_success(id):
    cur.execute("SELECT * FROM users NATURAL JOIN account WHERE id='{}';".format(id))
    user = cur.fetchall()[0]
    id = user[0]
    bal = user[2]
    rat = user[3]
    cur.execute("SELECT * FROM items")
    items = cur.fetchall()
    idx = len(items)
    cur.execute("with g as (select code, sum(trade_price) from trade group by code) select code from g where sum = (select max(g.sum) from g);")
    code = cur.fetchall()[0][0]
    cur.execute("SELECT type FROM category WHERE code = '{}'".format(code))
    bc = cur.fetchall()[0][0]
    cur.execute("with g as (select buyer, sum(trade_price) from trade group by buyer) select buyer from g where sum = (select max(g.sum) from g);")
    bb = cur.fetchall()[0][0]
    cur.execute("with g as (select seller, sum(trade_price) from trade group by seller) select seller from g where sum = (select max(g.sum) from g);")
    bs = cur.fetchall()[0][0]
    return render_template("main/main.html", id=id, bal=bal, rat=rat, items=items, idx=idx, bc=bc, bb=bb, bs=bs)


def change_rating(user):
    cur.execute("SELECT balance from account WHERE id='{}';".format(user))
    bal = cur.fetchall()[0][0]
    cur.execute("SELECT * from rating_info")
    info = cur.fetchall()
    for i in info:
        print(bal)
        print(i[1])
        if i[1] <= bal:
            cur.execute("UPDATE account SET rating = '{}' WHERE id = '{}'".format(i[0], user))
            connect.commit()
            break


@app.route('/')
def main():
    return render_template("login/login.html")


@app.route('/return_log', methods=['post'])
def re_turn_log():
    return render_template("login/login.html")


@app.route('/return_reg', methods=['post'])
def re_turn_reg():
    return render_template("register/register.html")


@app.route('/login', methods=['post'])
def login():
    send = request.form["send"]
    if send == "회원가입":
        return render_template("register/register.html")

    id = request.form["id"]
    password = request.form["password"]

    cur.execute("SELECT * FROM users WHERE id='{}';".format(id))
    result = cur.fetchall()
    print(send, id, password)

    if len(result) != 0:
        if result[0][1] == password:
            print("login success")
            return login_success(id)
        print("login fail: PW incorrect")

        return render_template("login/login_fail.html")
    print("login fail: ID not exist")

    return render_template("login/login_fail.html")


@app.route('/register', methods=['POST'])
def register():
    id = request.form["id"]
    password = request.form["password"]
    ref = request.form["reference"]
    send = request.form["send"]
    cur.execute("SELECT * FROM users WHERE id='{}';".format(id))
    result = cur.fetchall()
    print(send, id, password, ref)

    if 10 < len(id):
        print("invalid_ID")
        return render_template("register/invalid_ID.html")

    if len(result) != 0:
        print("ID_collision")
        return render_template("register/ID_collision.html")

    bal = 10000
    if ref != "":
        cur.execute("SELECT * FROM users WHERE id='{}';".format(ref))
        result = cur.fetchall()
        if len(result) == 0:
            return render_template("register/ref_not_exist.html")
        cur.execute("UPDATE account SET balance = balance + 5000 WHERE id='{}';".format(ref))
        change_rating(ref)
        connect.commit()
        bal += 15000
    else:
        ref = 'admin'
    cur.execute("INSERT INTO users VALUES('{}', '{}');".format(id, password))
    cur.execute("INSERT INTO account VALUES('{}', '{}', '{}', '{}')".format(id, bal, 'beginner', ref))
    connect.commit()
    print("register success")

    return re_turn_log()


@app.route('/admin', methods=['post'])
def admin():
    send = request.form["send"]
    if send == "유저정보":
        cur.execute("SELECT * FROM users NATURAL JOIN account;")
        result = cur.fetchall()
        return render_template("admin/print_table.html", users=result)

    if send == "거래내역":
        cur.execute("SELECT * FROM trade;")
        result = cur.fetchall()
        return render_template("admin/trade_info.html", trades=result)


@app.route('/trade', methods=['POST'])
def trade():
    send = request.form["send"]
    id = request.form["send_id"]
    if send == "판매":
        cur.execute("SELECT * FROM category")
        cate = cur.fetchall()
        return render_template("main/sell.html", category=cate, id=id)
    if send == "구매":
        cur.execute("SELECT balance,rating FROM account WHERE id='{}';".format(id))
        result = cur.fetchall()[0]
        bal = result[0]
        rat = result[1]
        idx = int(request.form["idx"]) - 1
        cur.execute("SELECT * from items;")
        item = cur.fetchall()
        if idx < 0 or len(item) <= idx:
            return login_success(id)
        item = item[idx]
        return render_template("main/buy.html", id=id, bal=bal, rat=rat, item=item)


@app.route('/add_sell', methods=['POST'])
def add_sell():
    send = request.form["send"]
    id = request.form["send_id"]
    if send!="취소":
        code = request.form["code"]
        name = request.form["name"]
        price = request.form["price"]
        stock = request.form["stock"]
        print(code, name, price, stock, id)
        cur.execute("SELECT name from items WHERE code ='{}' and name='{}' and price={} and seller='{}';".format(code, name, price, id))
        result = cur.fetchall()
        if len(result) == 0:
            cur.execute("INSERT INTO items VALUES('{}', '{}', {}, {}, '{}');".format(code, name, price, stock, id))
        else:
            cur.execute("UPDATE items set stock = stock + {} WHERE code ='{}' and name='{}' and price={} and seller='{}';".format(stock, code, name, price, id))
        connect.commit()

    return login_success(id)


@app.route('/buy_item', methods=['POST'])
def buy_item():
    send = request.form["send"]
    id = request.form["send_id"]

    if send!="취소":
        bal = int(request.form["send_bal"])
        rat = request.form["send_rat"]
        qty = int(request.form["quantity"])
        code = request.form["code"]
        name = request.form["name"]
        price = int(request.form["price"])
        stock = int(request.form["stock"])
        seller = request.form["seller"]

        cur.execute("SELECT * from rating_info")
        rating_info = cur.fetchall()
        disc = 0
        for r in rating_info:
            if r[0] == rat:
                disc = r[2]
                break

        if id == seller:
            print("본인구매")
            return login_success(id)

        if stock < qty:
            print("재고부족")
            return login_success(id)

        cost = qty*price*(100-disc)/100
        if bal - cost < 0:
            print("잔액부족")
            return login_success(id)


        cur.execute("UPDATE items set stock = stock - {} WHERE code ='{}' and name='{}' and price={} and seller='{}';".format(qty, code, name, price, seller))
        cur.execute("UPDATE account set balance = balance - {} WHERE id='{}';".format(cost, id))
        cur.execute("UPDATE account set balance = balance + {} WHERE id='{}';".format(cost, seller))
        cur.execute("INSERT INTO trade VALUES('{}', '{}', '{}', {});".format(id, seller, code, cost*qty))
        connect.commit()

        change_rating(id)
        change_rating(seller)

        print("구매성공")

        return login_success(id)

    return login_success(id)


if __name__ == '__main__':
    app.run()
