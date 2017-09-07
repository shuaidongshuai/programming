import threading
import time

def run(a,b):
	time.sleep(1)
	print(str(a)+ '--' +str(b) + '\n')

threads = []

for i in range(5):
	threads.append(threading.Thread(target = run,args = (1,2,)))

for thread in threads:
	thread.start()
for thread in threads:
	thread.join()
	