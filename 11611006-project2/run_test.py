import os
for i in range(1, 16):
	print(i)
	cmd = "./bin/splc < ./test/test_2_r%02d.spl > ./test/test_2_r%02d.out"%(i, i)
	# print(cmd)
	os.system(cmd)
	# val = os.system("diff ./test/test_2_r%02d_output.out ./test/test_2_r%02d.out "%(i, i))
	
	val = 0
	f1 = open("./test/test_2_r%02d_output.out"%i)
	text1 = []
	for line in f1:
		text1.append(line)
	f2 = open("./test/test_2_r%02d.out"%i)
	text2 = []
	for line in f2:
		text2.append(line)
	
	if (len(text1) == 0):
		print("Unknown")
	else:
		for i in range(0, len(text1)):
			if (text1[i] != text2[i]):
				val = 1
				print("diff line ", i, text1[i], text2[i])
		
		if (val == 0):
			print("Pass")
		else:
			print("Fail")
	
for i in range(1, 3):
	print(i)
	cmd = "./bin/splc < ./test/test_2_o%02d.spl > ./test/test_2_o%02d.out"%(i, i)
	# f = open("./test/test_2_o%02d_output.out"%(i), "w")
	# f.write("")
	# print(cmd)
	os.system(cmd)
os.system("./bin/splc < ./test/self_test.spl > ./test/self_test.out")
'''elif (val == 256):
		print("Different but may not Fail.")
		f = open("./test/test_2_r%02d.out"%(i))
		for line in f:
			print(line.strip("\n"))'''