from xmlrpc.server import SimpleXMLRPCRequestHandler,SimpleXMLRPCServer

class operations:
    def addition(self,x:int,y:int):
        return x+y

class requesthandler(SimpleXMLRPCRequestHandler):
    rpc_paths="/rpc"

def main():

    server=SimpleXMLRPCServer(('localhost',8080),requestHandler=requesthandler)
    server.register_instance(operations())

    print("server running on port 8080 fuckin nigga")
    server.serve_forever()

if __name__ == "__main__":
    main()