# coding=utf-8
import os
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
import time
import datetime
import socket 
from scipy.interpolate import make_interp_spline
from Data_Draw import *


if __name__=="__main__":
    #创建套接字
    tcpClientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('socket---%s'%tcpClientSocket)
    #链接服务器
    serverAddr = ('192.168.4.1',6666)
    while True:
        try:
            tcpClientSocket.connect(serverAddr)
            print('Connect success!')
            break
        except:
            print('Try connecting...')
            time.sleep(2)
    fig=plt.figure(figsize=(7.2, 8))
    filename = './data.txt'

    if not os.path.exists(filename):
        open(filename, "w")
    while True:
        # # 发送数据
        # sendData="Hello"
        # if len(sendData) > 0:
        #     tcpClientSocket.send(bytes(sendData.encode('utf-8')))                                                                                                 
        # else:
        #     break
        #接收数据
        recvData = tcpClientSocket.recv(1024)
        #打印接收到的数据
        # print(recvData)
        temperature = ((0x00ff & recvData[0]) << 8 ) | recvData[1]
        Humidity    = ((0x00ff & recvData[2]) << 8 ) | recvData[3]
        Co2eq       = ((0x00ff & recvData[4]) << 8 ) | recvData[5] 
        TVOC        = ((0x00ff & recvData[6]) << 8 ) | recvData[7]
        ADC         = ((0x00ff & recvData[8]) << 8 ) | recvData[9]
        temperature =  float(temperature)/10
        Humidity    =  float(Humidity)/10
        ADC         =  float(ADC)/10000
        timeStamp   =  time.time()
        nowtime     =  time.strftime("%Y-%m-%d %H:%M:%S", time.localtime( time.time() ) )
        print(nowtime,": ",temperature,"C ", Humidity,"% ", Co2eq,"Ppm ", TVOC,"Ppb "+str(ADC))
        dat = str(nowtime)+' '+str(temperature)+' '+str(Humidity)+' '+str(Co2eq)+' '+str(TVOC)+' '+str(ADC)+' '+str(timeStamp)+'\r'

        with open(filename, "a") as f:
            f.write(dat)
            f.close
        
        # Draw_Data(fig)


    #关闭套接字
    tcpClientSocket.close()
    print('close socket!')