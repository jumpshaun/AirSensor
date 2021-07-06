
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import time
import datetime
import numpy as np
from scipy.interpolate import make_interp_spline
# 平滑插值
def smooth(x,y,times):
    x=np.array(x)
    y=np.array(y)
    x_smooth = np.linspace(x.min(), x.max(), len(x)*times)
    y_smooth = make_interp_spline(x, y)(x_smooth)
    return x_smooth,y_smooth

# 零阶保持器
def Zero_Holder(strs,times):
    out=[]
    for s in strs:
        for i in range(times):
            out.append(str(s))
    return out

# 平均滤波算法
def ArithmeticAverage(inputs,per):
	if np.shape(inputs)[0] % per != 0:
		lengh = np.shape(inputs)[0] / per
		for x in range(int(np.shape(inputs)[0]),int(lengh + 1)*per):
			inputs = np.append(inputs,inputs[np.shape(inputs)[0]-1])
	inputs = inputs.reshape((-1,per))
	mean = []
	for tmp in inputs:
		mean.append(tmp.mean())
	return mean
def Stamp2Str(timeStamp):
    return datetime.datetime.utcfromtimestamp(timeStamp+8*3600).strftime("%Y-%m-%d %H:%M:%S.%f")


import matplotlib.ticker as mticker
import pylab as pl

  
def Draw_Data(fig):
    Stamptimes,timeStrs,Smooth_timeStrs,Smooth_hourmin,temps,humis,co2s,tvocs,adcs=[],[],[],[],[],[],[],[],[]  
    with open(r"./data.txt", "r") as f:
        for line in f.readlines():
            data= line.split(' ')
            if(  float(data[7])+24*3600 > time.time()):
                Stamptimes.append(float(data[7]))
                temps.append(float(data[2]))
                humis.append(float(data[3]))  
                co2s.append(int(data[4]))
                tvocs.append(int(data[5]))
                adcs.append(float(data[6]))
    
    if(len(Stamptimes)<5):
        return 0

    ## 平滑插值
    scale = 3 # 插值倍数
    _,Smooth_temps=smooth(Stamptimes, temps, scale)  
    _,Smooth_humis=smooth(Stamptimes, humis, scale)
    _,Smooth_co2s=smooth(Stamptimes, co2s, scale)
    Smooth_timeStamps,Smooth_tvocs=smooth(Stamptimes, tvocs, scale)
    
    for stamps in Smooth_timeStamps:
        Smooth_timeStrs.append(Stamp2Str(stamps))

    for timeStrs in Smooth_timeStrs:
        Smooth_hourmin.append(timeStrs[11:16])

    plt.ion()
    plt.clf()  #清除上一幅图像
    ax1=fig.add_subplot(411)
    ax1.plot(Smooth_timeStrs,Smooth_temps,color='forestgreen',label='Temperature($^\circ$C)')
    ax1.set_xticks([])
    plt.legend(loc="upper right")

    ax2=fig.add_subplot(412)
    ax2.plot(Smooth_timeStrs,Smooth_humis,color='royalblue',label='Humidity(%)')
    ax2.set_xticks([])
    plt.legend(loc="upper right")

    ax3=fig.add_subplot(413)
    ax3.plot(Smooth_timeStrs,Smooth_co2s,color='grey',label='Co2(Ppm)')
    ax3.set_xticks([])
    plt.legend(loc="upper right")

    ax4=fig.add_subplot(414)
    ax4.plot(Smooth_timeStrs,Smooth_tvocs,color='goldenrod',label='TVOC(Ppb)')
    ax4.xaxis.set_major_locator(ticker.MultipleLocator(base=len(Smooth_hourmin)/5))
    

    plt.xticks(rotation=15)
    plt.tick_params(axis='x', labelsize=9)  
    plt.legend(loc="upper right")
    plt.show()
    plt.pause(1)
    plt.ioff()  # 关闭画图的窗口

if __name__=="__main__":
  
    fig=plt.figure(figsize=(7, 7))
    while True:
        Draw_Data(fig)
        plt.pause(0)

    





    




