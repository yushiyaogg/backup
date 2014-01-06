使用方法：
1.声明一个TimerManager类型的全局变量：g_TimerManager
2.在main函数中执行g_TimerManager.init()
3.重写Timer继承类的doAction()，当定时器到期后此函数将被调用
4.有新的定时器请求时，调用该定时器对象的attachTimer(int epollfd)成员函数既可，参数epollfd为该线程的epoll循环的EpollFd；若需解除，则调用它的detachTimer()成员函数
5.若需要修改某定时器的到期时间，调用updateExpiredTime(int)饥渴，参数为新的到期时间，单位为秒