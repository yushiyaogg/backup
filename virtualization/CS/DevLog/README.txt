ʹ�÷�����
(1)����һ��ȫ�ֱ���g_pDevLog(���ܸ�������)
DevLog *g_pDevLog = NULL;

(2)ʹ����������д������־
DEV_LOG(LOG_LEVEL level, LOG_OUT_TYPE outtype, string msg);
��¼��־��ͨ�ú꣬level�Ǽ���outtype���������, msg�Ǵ�����Ϣ
LOG_OUT_TYPE��ʾ��־��������ͣ������֣�OUT_SCRֻ�������Ļ��OUT_FILEֻ������ļ���OUT_BOTH��Ļ��ӡ����������ļ�

DEV_LOG_ERROR(string msg);
�ڳ���ʱ�øú��¼��־���ȼ���DEV_LOG(LERROR, OUT_BOTH, msg);

DEV_LOG_FUNC();
����Ҫ�ĺ�����ڴ���ӣ��޲�����


========================================================================================
�ӿ�˵����

1.���캯��
DevLog();//�޲������Զ�������־�ļ������ļ�����ʽΪ��log_ʱ�䡱�����磺log_213548
ʹ�øù��캯��ʱ��ÿ�����ɵ��ļ�������ͬ

DevLog(const char* logName);//����Ϊ��־�ļ���
ʹ�øù��캯����ÿ�ζ�д��ָ�����ļ��У�������������Զ�����������Ѿ����������ļ�β��append

2.������־����
int setLogLevel(LOG_LEVEL level);
level��ȡֵ������LEVEL_NOE, LEVEL_LOW, LEVEL_MIDDLE, LEVEL_HIGH


3.д��־
int writeLog(LOG_LEVEL type, LOG_OUT_TYPE outtype, const std::string& message);
type��ʾ��־�����ͣ�ȡֵ���£�
LINFO=0,  //һ����Ϣ����Ҫ�Ǹ���xml�����ݽϳ�
LDEBUG,   //������Ϣ����ĳ��������ֵ
LFUNC,    //���뺯��������Ҫ�ĺ�����ڴ�ʹ��
LEVENT,   //ҵ���¼����磺�յ��ͻ��˷���������Ϣ����ʼ���ܵȣ����ݽ϶�
LWARNING, //����
LERROR,   //һ����󣬵�ǰ����������Ǻ������̻��ܼ���ִ��
LFATAL    //�������󣬷����ô���󣬳�������˳�

LOG_OUT_TYPE��ʾ��־��������ͣ������֣�OUT_SCRֻ�������Ļ��OUT_FILEֻ������ļ���OUT_BOTH��Ļ��ӡ����������ļ�

�������Ļʱ����ӡ����ɫ�������£�
LINFO�� //��ɫ
LDEBUG, //��ɫ
LFUNC, //��ɫ
LEVENT, //ҵ���¼�����ɫ 
LWARNING, //����,��ɫ
LERROR, //һ����󣬺�ɫ
LFATAL//�������󣬺�ɫ

4 ��ӷָ���
int insertSeparatorLine(int n);
����n��ʾ����n���ָ��У��ָ��е�����Ĭ��Ϊ���У�����ͨ��setLineSeparator����
int setLineSeparator(const std::string &line);


