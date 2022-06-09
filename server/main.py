from requests import *
from flask import Flask, redirect, url_for, request, abort, make_response
import pymysql
import json
import hashlib
import uuid
import time
import base64
import cryptography

app = Flask(__name__)

# This is a sample Python script.


testint = 0;


# 数据库连接
db = pymysql.connect(host='localhost',
                     user='user1',
                     password='n4zy2c/.lrsT',
                     database='sdu19_efly')


def check_cookie(uid: str, user_session: str) -> int:
    if user_session is None or uid is None:
        return 0
    if '"' in uid or '"' in user_session:
        return -1
    sql = 'select * from user_session where uid = "' + uid + '" and session = "' + user_session + '";'
    cursor = db.cursor()
    cursor.execute(sql)
    result = cursor.fetchall()
    if len(result) == 0:
        return 0

    return 1


@app.route('/test/')
def test():
    return 'test'


# 登录，设置cookie
@app.route('/login/', methods=['POST'])
def login():
    print("login_start")
    # global testint
    #if testint > 0:
    #    abort(418)
    # testint += 1
    if request.headers.get('Content-Type') == 'application/json':
        j_data = request.get_json()
        username = j_data['username']
        if '`' in username:
            abort(400)
            return
        password = username + j_data['password']
        print(username, ' ', password)
        sh = hashlib.sha256()
        sh.update(password.encode('utf-8'))
        print(sh.hexdigest(), ' login_hash')
        sql = 'select uid from user where username="'\
              + username + '" and passwd="' + sh.hexdigest() + '";'
        cursor = db.cursor()
        cursor.execute(sql)
        result = cursor.fetchall()
        if len(result) == 0:
            abort(401)
            return
        uid = result[0][0]
        user_session = str(uuid.uuid4())
        sql = 'insert into user_session (uid, session,time)value ("' \
              + str(uid) + '", "' + user_session + '", ' + str(int(time.time())) + ');'
        cursor2 = db.cursor()
        cursor2.execute(sql)
        db.commit()
        resp = make_response('success')
        resp.set_cookie('uid', str(uid))
        resp.set_cookie('user_session', user_session)
        # testint -= 1
        return resp
    else:
        abort(400)


@app.route('/query/<table_name>/', methods=['POST'])
def query(table_name):
    if table_name == 'user' or '`' in table_name:
        abort(403)
        return
    uid = request.cookies.get('uid')
    user_session = request.cookies.get('user_session')
    print(uid, ' ', user_session, ' query')
    # j_data = request.get_json()
    # print(str(j_data))
    # print(len(str(j_data)))
    is_logged_in = check_cookie(uid, user_session)
    print(is_logged_in)
    if is_logged_in == 0:
        abort(401)
    # sql = 'select * from user_session where uid = "' + uid + '" and user_session = "' + user_session + '";'
    # cursor = db.cursor()
    # cursor.execute(sql)
    # result = cursor.fetchall()
    # if len(result) == 0:
    #     abort(401)
    #     return
    if request.headers.get('Content-Type') == 'application/json':
        j_data = request.get_json()
        #if len(str(j_data)) < 20:

    else:
        abort(400)
    sql = 'select * from `' + table_name + '`;'
    cursor = db.cursor()
    cursor.execute(sql)
    results = cursor.fetchall()
    return str(results)


@app.route('/airport/', methods=['POST'])
def airport(table_name):
    uid = request.cookies.get('uid')
    user_session = request.cookies.get('user_session')
    print(uid, ' ', user_session, ' query')
    # j_data = request.get_json()
    # print(str(j_data))
    # print(len(str(j_data)))
    is_logged_in = check_cookie(uid, user_session)
    print(is_logged_in)
    if is_logged_in == 0:
        abort(401)
    # sql = 'select * from user_session where uid = "' + uid + '" and user_session = "' + user_session + '";'
    # cursor = db.cursor()
    # cursor.execute(sql)
    # result = cursor.fetchall()
    # if len(result) == 0:
    #     abort(401)
    #     return
    if request.headers.get('Content-Type') == 'application/json':
        j_data = request.get_json()
        #if len(str(j_data)) < 20:

    else:
        abort(400)
    sql = 'select * from airport;'
    cursor = db.cursor()
    cursor.execute(sql)
    results = cursor.fetchall()
    return str(results)


def main():
    print(str(int(time.time())))
    cursor = db.cursor()
    sql = 'select * from airport;'
    cursor.execute(sql)
    results = cursor.fetchall()
    print(str(results))
    for row in results:
       print(row[0])
    app.run('0.0.0.0', 10086)


if __name__ == '__main__':
    main()


