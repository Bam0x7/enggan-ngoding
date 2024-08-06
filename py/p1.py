name = ""
age = 0

def print_data():
    global name
    global age

    print(f"name: {name}")
    print(f"age: {age}")
    if age < 18:
        print(f"usia belum mencukupi")
    else:
        print("selamat datang di hiburan sore:v")    

def input_data():
    global name
    global age

    name = input("name: ")
    age = int(input("age: "))
    print_data()

if __name__ == '__main__':
    input_data()    