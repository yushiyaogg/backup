ʹ�÷�����
1.����һ��TimerManager���͵�ȫ�ֱ�����g_TimerManager
2.��main������ִ��g_TimerManager.init()
3.��дTimer�̳����doAction()������ʱ�����ں�˺�����������
4.���µĶ�ʱ������ʱ�����øö�ʱ�������attachTimer(int epollfd)��Ա�����ȿɣ�����epollfdΪ���̵߳�epollѭ����EpollFd�������������������detachTimer()��Ա����
5.����Ҫ�޸�ĳ��ʱ���ĵ���ʱ�䣬����updateExpiredTime(int)���ʣ�����Ϊ�µĵ���ʱ�䣬��λΪ��