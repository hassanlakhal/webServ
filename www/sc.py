from flask import Flask, make_response

app = Flask(__name__)

@app.route('/')
def set_cookie():
    resp = make_response("Cookie is set!")
    resp.set_cookie('user', 'John Doe')
    return resp

if __name__ == '__main__':
    app.run(debug=True)
