import os
import cherrypy

PATH = os.path.abspath(os.path.dirname(__file__))

conf = {
    "/documento": {
        "tools.staticfile.on": True,
        "tools.staticfile.filename": os.path.join(PATH, "Ex6.html")
    }
}


class Node(object):
    @cherrypy.expose
    def index(self):
        return "Eu sou o índice do Node (Node.index)"

    @cherrypy.expose
    def page(self):
        return "Eu sou um método do Node (Node.page)"


class HTML(object):
    @cherrypy.expose
    def index(self):
        with open("Ex6.html", 'r') as f:
            content = f.read()

        return content


class Actions(object):
    @cherrypy.expose
    def doLogin(self, username=None, password=None):
        if username == "user" and password == "pass":
            return "Acesso concedido para o usuário " + username
        else:
            return "Acesso negado para o usuário " + username


class Root(object):
    def __init__(self):
        self.node = Node()
        self.html = HTML()
        self.actions = Actions()

    @cherrypy.expose
    def index(self):
        return "Eu sou o índice do Root (Root.index)"

    @cherrypy.expose
    def page(self):
        return "Eu sou um método do Root (Root.page)"

    @cherrypy.expose
    def form(self):
        cherrypy.response.headers["Content-Type"] = "text/html"
        return open("Ex7.html")

    @cherrypy.expose
    def actions(self):
        return self.actions


if __name__ == "__main__":
    cherrypy.quickstart(Root(), "/", config=conf)
