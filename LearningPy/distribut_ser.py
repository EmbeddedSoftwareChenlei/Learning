# -*- coding: utf-8 -*-
# server
import queue
import multiprocessing
from multiprocessing import freeze_support
from multiprocessing.managers import BaseManager
import logging as log

task_queue = queue.Queue()
result_queue = queue.Queue()

# 从BaseManager继承的QueueManager:
class QueueManager(BaseManager):
	pass

def get_task_queue():
    global task_queue
    return task_queue
 
def get_result_queue():
    global result_queue
    return result_queue

def init_ser(addr,port,authkey):

	# 把两个Queue都注册到网络上, callable参数关联了Queue对象:
	QueueManager.register('get_task_queue', callable=get_task_queue)
	QueueManager.register('get_result_queue', callable=get_result_queue)

	manager = QueueManager(address=(addr,port), authkey=authkey)

	return manager

def main():
	log.basicConfig(level='NOTSET', 
		format='%(asctime)s [%(levelname)s] %(message)s',
                datefmt='%Y:%m:%d %H:%M:%S')

	authkey = b'abc'
	addr = '127.0.0.1'
	port = 5000

	log.info('listen %s:%d', addr, port)

	manager = init_ser(addr, port, authkey)

	ser = manager.get_server()
	ser.serve_forever()

if __name__=='__main__':
	freeze_support()
	main()
