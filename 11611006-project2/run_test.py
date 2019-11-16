import os
for i in range(1, 16):
	print(i)
	cmd = "./bin/splc < ./test/test_2_r%02d.spl > ./test/test_2_r%02d.out"%(i, i)
	# print(cmd)
	os.system(cmd)
for i in range(1, 3):
	print(i)
	cmd = "./bin/splc < ./test/test_2_o%02d.spl > ./test/test_2_o%02d.out"%(i, i)
	# print(cmd)
	os.system(cmd)
os.system("./bin/splc < ./test/self_test.spl > ./test/self_test.out")