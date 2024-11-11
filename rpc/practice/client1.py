import xmlrpc.client

def main():
    
    proxy=xmlrpc.client.ServerProxy("http://localhost:8080/rpc")

    while(True):
        print("1.add\n2.subtract\n3.multiply")

        choice=int(input("enter choice :"))
        
        if(choice==1):
            x=int(input("enter x :"))
            y=int(input("enter y :"))

            result=proxy.addition(x,y)
            print(f"addition is :{result}")
        
        else:
            break

if __name__ == "__main__":
    main()