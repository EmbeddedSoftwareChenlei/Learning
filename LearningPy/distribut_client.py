# -*- coding: utf-8 -*-
from multiprocessing.managers import BaseManager
import logging as log
import time
import queue

# 从BaseManager继承的QueueManager:
class QueueManager(BaseManager):
	pass

def init_ser(addr,port,authkey):

	# 把两个Queue都注册到网络上, callable参数关联了Queue对象:
	QueueManager.register('get_task_queue')
	QueueManager.register('get_result_queue')

	manager = QueueManager(address=(addr,port), authkey=authkey)

	return manager

def main():
	log.basicConfig(level='NOTSET', 
		format='%(asctime)s [%(levelname)s] %(message)s',
                datefmt='%Y:%m:%d %H:%M:%S')

	authkey = b'abc'
	addr = '127.0.0.1'
	port = 5000

	log.info('conect to %s:%d ...', addr, port)

	manager = init_ser(addr, port, authkey)

	while True:
		try:			
			manager.connect()
			log.info('connect to %s:%d suc'%(addr,port))			
			run_pro(manager)
		except Exception as e:
			log.info(e)
			time.sleep(1)

def run_pro(manager):	
	is_closed = False
	while not is_closed:
		try:
			task_queue = manager.get_task_queue()
			task = task_queue.get(timeout=1)
			log.info('get one')		
		except queue.Empty as e:
			log.info('timeout')
		except Exception as e:
			log.info(e)
			time.sleep(1)
			is_closed = True

if __name__=='__main__':
	main()
