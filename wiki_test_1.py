#!/usr/bin/python
# -*- coding: utf-8 -*-
#Andre Torres JUN2016                                                                                                                 #Does not save manual queries to db 
                       
import serial
import socketIO_client
import sys

#program help
if len(sys.argv)==1 :
    print 'HELP \n syntax:\t wiki_test_1.py port\n ex:\t wiki_test_1.py /dev/ttyACM0\n'
    sys.exit();

#print connected port
print '\n port: '
print sys.argv[1];
port=sys.argv[1]; 

domain_list=['en.wikipedia.org','pt.wikipedia.org']		#domains to compare


class WikiNamespace(socketIO_client.BaseNamespace):
	def on_change(self, change):
		#print('%(user)s edited %(title)s' % change)	#print on terminal
		serial_port=serial.Serial( port ,9600)  		#Open serial connection; 9600 Baud rate
		domain= '%(server_name)s' %change 				#get domain name
		print( domain)									#print domain name in term
		
		#filter results by domain
		for i in xrange(0,len(domain_list)):
			if (domain == domain_list[i]):
				serial_port.write(str(i))				#send char through serial port

		serial_port.close()								#close serial connection
						
	def on_connect(self):
		self.emit('subscribe', '*.wikipedia.org' ) #commons.wikimedia.org

socketIO = socketIO_client.SocketIO('stream.wikimedia.org', 80)
socketIO.define(WikiNamespace, '/rc')
socketIO.wait()
	

