import os

def cmpFile(path1, path2):
    val = 0
    f1 = open(path1)
    text1 = []
    for line in f1:
        text1.append(line)
    f2 = open(path2)
    text2 = []
    for line in f2:
        text2.append(line)
    
    if (len(text1) != len(text2)):
        print("Fail!!!")
    else:
        for i in range(0, len(text1)):
            if (text1[i] != text2[i]):
                val = 1
                print("diff line ", i)
                print("In file 1:", text1[i])
                print("In file 2:", text2[i])
        
        if (val == 0):
            print("Pass")
        else:
            print("Fail")

def cpFile(fromPath, toPath):
    cmd = "cp " + fromPath + " " + toPath
    os.system(cmd)

for i in range(1, 16):
    print(i)
    cmd = "./bin/splc ./test/test_2_r%02d.spl"%(i)
    # print(cmd)
    os.system(cmd)
    cmpFile("./test/test_2_r%02d.out"%i, "./test/test_2_r%02d.output.out"%i)
    # cpFile("./test/test_2_r%02d.out"%i, "./test/test_2_r%02d.output.out"%i);
    
    
for i in range(1, 3):
    print(i)
    cmd = "./bin/splc ./test/test_2_o%02d.spl"%(i)
    # f = open("./test/test_2_o%02d_output.out"%(i), "w")
    # f.write("")
    # print(cmd)
    os.system(cmd)
    cmpFile("./test/test_2_o%02d.out"%i, "./test/test_2_o%02d.output.out"%i)
    # cpFile("./test/test_2_o%02d.out"%i, "./test/test_2_o%02d.output.out"%i);
    
for i in range(1, 6):
    print(i)
    cmd = "./bin/splc ./test/self_test_%02d.spl"%(i)
    os.system(cmd)
    cmpFile("./test/self_test_%02d.out"%i, "./test/self_test_%02d.output.out"%i)
    # cpFile("./test/self_test_%02d.out"%i, "./test/self_test_%02d.output.out"%i);