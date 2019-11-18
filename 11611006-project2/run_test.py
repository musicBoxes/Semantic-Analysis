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

for i in range(1, 16):
	print(i)
	cmd = "./bin/splc < ./test/test_2_r%02d.spl > ./test/test_2_r%02d.out"%(i, i)
	# print(cmd)
	os.system(cmd)
	# val = os.system("diff ./test/test_2_r%02d_output.out ./test/test_2_r%02d.out "%(i, i))
	cmpFile("./test/test_2_r%02d.out"%i, "./test/test_2_r%02d_output.out"%i)
	
	
for i in range(1, 3):
	print(i)
	cmd = "./bin/splc < ./test/test_2_o%02d.spl > ./test/test_2_o%02d.out"%(i, i)
	# f = open("./test/test_2_o%02d_output.out"%(i), "w")
	# f.write("")
	# print(cmd)
	os.system(cmd)
	cmpFile("./test/test_2_o%02d.out"%i, "./test/test_2_o%02d_output.out"%i)
	
# os.system("./bin/splc < ./test/self_test.spl > ./test/self_test.out")