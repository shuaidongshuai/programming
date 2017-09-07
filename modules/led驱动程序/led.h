//一下参数都不重要   重要的是  _IO（）这个宏 	 他可以确定一个命令
#define Magic 'd'
#define LED_ON _IO(Magic,0)	//1类型（幻数）表明是属于那个设备，2序号，用来区分同一设备的不同命令   这里 ‘d’ 和 0  1 都可以随便设置 只要不冲突 
#define LED_OFF _IO(Magic,1)