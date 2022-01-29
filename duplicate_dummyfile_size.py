def write_row(file_, *columns):
    print(*columns, sep='\t', end='\n', file=file_)


for i in range(1):
    
    f = open("dummyfile.txt", "r")
    text = f.read()
    f.close()
    file = open("dummyfile.txt", "a")
    write_row(file,text)
   
    file.close()

