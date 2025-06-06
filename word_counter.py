



with open("README.md","r") as file:
    # print(file.read())
    file = file.read().split("\n")
    reading = False
    erick = 0
    for line in file:
        if not reading and line == "## scenario":
            reading = True
        if reading:
            erick += len(line.split(" "))
    print(erick)

