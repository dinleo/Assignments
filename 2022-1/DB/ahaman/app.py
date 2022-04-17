import psycopg2
from flask import Flask, render_template, request

app = Flask(__name__)
connect = psycopg2.connect("dbname=postgres user=postgres password=1127")
cur = connect.cursor()  # create cursor


@app.route('/')
def main():
    return render_template("main.html")


@app.route('/return', methods=['post'])
def re_turn():
    return render_template("main.html")


@app.route('/print_table', methods=['post'])
def print_table():
    cur.execute("SELECT * FROM users;")
    result = cur.fetchall()

    return render_template("print_table.html", users=result)


@app.route('/register', methods=['post'])
def register():
    id = request.form["id"]
    password = request.form["password"]
    send = request.form["send"]
    cur.execute("SELECT * FROM users WHERE id='{}';".format(id))
    result = cur.fetchall()
    print(send, id, password)
    if send == "sign up":
        if len(result) != 0:
            print("ID_collision")
            return render_template("ID_collision.html")
        cur.execute("INSERT INTO users VALUES('{}', '{}');".format(id, password))
        connect.commit()
        print("register success")
        return re_turn()
    if send == "login":
        if len(result) != 0:
            if result[0][1] == password:
                print("login success")
                return render_template("login_success.html")
            print("login fail: PW incorrect")
            return render_template("login_fail.html")
        print("login fail: ID not exist")
        return render_template("login_fail.html")


if __name__ == '__main__':
    app.run()
