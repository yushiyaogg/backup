/*
 * =====================================================================================
 *
 *       Filename:  I_Manager_Agent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/22/12 17:51:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "I_Manager_Agent.h"

I_Manager_Agent::I_Manager_Agent()
{
    //this->fd = I_fd;
    //state = 0;
    sn = 0;
    BHSbuff.new_buff(BHS_LEN);
    paddingbuf.new_buff(3);
    max_cmd_sn = 0;
    i_agent = NULL;
    read_stat = READ_BHS;

    //I_read.read_type = BHS;
    //I_read.read_len = BHS_LEN;

    //I_write.write_type = BHS;
    //I_write.write_len = BHS;
}

I_Manager_Agent::~I_Manager_Agent()
{
    BHSbuff.delete_buff();
    Databuff.delete_buff();
}

/*int I_Manager_Agent::getfd()
{
    return fd;
}*/

/*int I_Manager_Agent::init_read(int len, class Buffermanager* buff)
{
    delete buff->bufferptr;
    buff->bufferptr = new(unsigned char[len]);
    buff->buff_length = len;
    I_read.read_len = len;
    I_read.read_complete = false;
}*/

char* I_Manager_Agent::find_key(char* searchkey, void* text,int text_len)
{
    char *_data_, *key, *value;
    int keylen, datasize;
    keylen = strlen(searchkey);
    _data_ =(char *) text;
    datasize = text_len;

    while(1)
    {
        for(key = _data_; datasize > 0 && *_data_ != '='; _data_ ++ , datasize--)
            ;
        if(!datasize)
            return NULL;
        _data_ ++;
        datasize --;

        for(value = _data_; datasize > 0&& *_data_ != 0; _data_++, datasize--)
            ;
        _data_++;
        datasize --;

        if(keylen == value - key - 1 && !strncmp(key,searchkey,keylen))
            return value;
    }

}

int I_Manager_Agent::exec()
{
        memcpy(BHSbuff.bufferptr,i_agent->Readbuff_head.bufferptr,BHS_LEN);
        pdu.bhs = (struct iscsi_hdr*)(BHSbuff.bufferptr);
        pdu.Datasize =(( pdu.bhs->datalength[0]<<16) +(pdu.bhs->datalength[1]<<8)+pdu.bhs->datalength[2]);
        Databuff.delete_buff();
        if(pdu.Datasize > 0)
        {
            Databuff.new_buff(pdu.Datasize);
            memcpy(Databuff.bufferptr,i_agent->Readbuff_data.bufferptr,pdu.Datasize);
        }
        if(0 > cmnd_exec())
        {
            cout <<"cmnd_exec error"<< endl;
            return -1;
        }
        return 0;
}



int I_Manager_Agent::cmnd_exec()
{
    switch(pdu.bhs->opcode & ISCSI_OPCODE_MASK)
    {
    case ISCSI_OP_LOGIN_CMD:
       /* if(state == STATE_LOGIN_FULL)
        {
            cout <<"login error"<<endl;
            return -1;
        }*/
        if(cmnd_exec_login() < 0)
        {
            cout <<"cmnd_exec_login error "<< endl;
            return -1;
        }
        else
            return 0;
        
    case ISCSI_OP_TEXT_CMD:
       if(cmnd_exec_text() < 0)
       {
            cout <<"cmnd_exec_text error"<<endl;
            return -1;
       } 
       else
           return 0;
    case ISCSI_OP_SCSI_CMD:
       if(cmnd_exec_scsi() < 0)
       {
            cout << "cmnd_exec_scsi error"<< endl;
            return -1;
       }
       else
           return 0;
    case ISCSI_OP_DATAOUT_CMD:
        if(cmnd_exec_dataout() < 0)
        {
            cout << "cmnd_exec_dataout error"<<endl;
        }
        else
            return 0;
    case ISCSI_OP_LOGOUT_CMD:
       if(cmnd_exec_logout() < 0)
       {
            cout << "cmnd_exec_logout error" << endl;
            return -1;
       }
       return 0;
    case ISCSI_OP_NOP_OUT:
       if(cmnd_exec_nop_out() < 0)
       {
            cout << "cmnd_exec_nop_out error" << endl;
            return -1;
       }
       return 0;
    default:
       cout << "other kinds of command"<< endl;
       return 0;
    }
}

int I_Manager_Agent::cmnd_exec_login()
{
    login_req_hdr = (struct iscsi_login_req_hdr*)pdu.bhs;
   /* login_rsp_hdr->opcode = ISCSI_OP_LOGIN_RSP;
    login_rsp_hdr->max_version = 0;
    login_rsp_hdr->active_version = 0;
    login_rsp_hdr->itt = login_req_hdr->itt;
    login_rsp_hdr->sid = login_req_hdr->sid;*/
    switch(login_req_hdr->flag & ISCSI_FLG_CSG_MASK){
    case ISCSI_FLG_CSG_SECURITY:
        cout << "CSG_SECURITY"<<endl;
       // state_exec_security();
        return 0;

    case ISCSI_FLG_CSG_LOGIN:
        state_exec_login();
        return 0;
    }
}

/*int I_Manager_Agent::state_exec_security()
{

       // state = STATE_SECURITY;
        
        I_read.read_socket(fd,&paddingbuf);
        paddingbuf.delete_buff();

        char *s_type;
        char key[] = "SessionType";
        s_type = find_key(key,Databuff.bufferptr,Databuff.buff_length);
        if(strcmp(s_type,"Discovery") == 0)
        {
            session_type = DISCOVERY;
        }
        else if(strcmp(s_type,"Normal") == 0)
        {
            session_type = NORMAL;
        }
        else
        {
            cout << "session type error" << endl;
            return -1;
        }

        login_rsp_hdr.opcode = ISCSI_OP_LOGIN_RSP;
        login_rsp_hdr.flag = login_req_hdr->flag;
        login_rsp_hdr.max_version = 0;
        login_rsp_hdr.active_version = 0;
        login_rsp_hdr.ahslength = 0;


        login_rsp_hdr.sid = login_req_hdr->sid;
        login_rsp_hdr.itt = login_req_hdr->itt;

        login_rsp_hdr.stat_sn = htonl(sn);
        sn ++;

        login_rsp_hdr.exp_cmd_sn =htonl( ntohl(login_req_hdr->cmd_sn));
        login_rsp_hdr.max_cmd_sn =htonl( ntohl(login_req_hdr->cmd_sn) + 1);

        Databuff.delete_buff();
        char key_value1[] = "TargetPortalGroupTag=1";
        Databuff.add_buff(key_value1,sizeof(key_value1));
        char key_value2[] = "AuthMethod=None";
        Databuff.add_buff(key_value2,sizeof(key_value2));
        char padding[]= "";
        Databuff.add_buff(padding,sizeof(padding));

        int n_datalen = htonl(Databuff.buff_length - 1);//padding
        unsigned char datalen[4];
        memcpy(datalen,&n_datalen,sizeof(int));
        memcpy(&(login_rsp_hdr.datalength),&datalen[1],3);

        BHSbuff.delete_buff();
        BHSbuff.add_buff(&login_rsp_hdr, BHS_LEN);
        return 0;
}*/

int I_Manager_Agent::state_exec_login()
{
        
        char *s_type;
        char key[] = "SessionType";
        int padding_number;
        s_type = find_key(key,Databuff.bufferptr,Databuff.buff_length);
        if(strcmp(s_type,"Discovery") == 0)
        {
            session_type = DISCOVERY;
        }
        else if(strcmp(s_type,"Normal") == 0)
        {
            session_type = NORMAL;
        }
        else
        {
            cout << "session type error" << endl;
            return -1;
        }

        login_rsp_hdr.opcode = ISCSI_OP_LOGIN_RSP;
        login_rsp_hdr.flag = login_req_hdr->flag;
        login_rsp_hdr.max_version = 0;
        login_rsp_hdr.active_version = 0;
        login_rsp_hdr.ahslength = 0;

        memcpy(&(login_rsp_hdr.sid.id.isid),&(login_req_hdr->sid.id.isid),6);
        


        login_rsp_hdr.itt = login_req_hdr->itt;

        login_rsp_hdr.stat_sn = htonl(sn);
        sn ++;

        if(htonl(login_req_hdr->cmd_sn) > max_cmd_sn)
            max_cmd_sn = htonl(login_req_hdr->cmd_sn);

        login_rsp_hdr.exp_cmd_sn = htonl(max_cmd_sn) ;
        login_rsp_hdr.max_cmd_sn = htonl(max_cmd_sn + 1);

        Databuff.delete_buff();
        if(session_type == DISCOVERY)
        {

            login_rsp_hdr.sid.id.tsih = 1;
            char key_value1[] = "TargetPortalGroupTag=1";
            Databuff.add_buff(key_value1,sizeof(key_value1));
            char key_value2[] = "HeaderDigest=None";
            Databuff.add_buff(key_value2,sizeof(key_value2));
            char key_value3[] = "DataDigest=None";
            Databuff.add_buff(key_value3,sizeof(key_value3));
            char key_value4[] = "DefaultTime2Wait=2";
            Databuff.add_buff(key_value4,sizeof(key_value4));
            char key_value5[] = "DefaultTime2Retain=0";
            Databuff.add_buff(key_value5,sizeof(key_value5));
            char key_value6[] = "IFMarker=No";
            Databuff.add_buff(key_value6,sizeof(key_value6));
            char key_value7[] = "OFMarker=No";
            Databuff.add_buff(key_value7,sizeof(key_value7));
            char key_value8[] = "ErrorRecoveryLevel=0";
            Databuff.add_buff(key_value8,sizeof(key_value8));
           /* char padding[] = "";
            Databuff.add_buff(padding,sizeof(padding));
            Databuff.add_buff(padding,sizeof(padding));*/
            int n_datalen = htonl(Databuff.buff_length );
            unsigned char datalen[4];
            memcpy(datalen,&n_datalen,sizeof(int));
            memcpy(&(login_rsp_hdr.datalength),&datalen[1],3);
            padding_number = Databuff.buff_length;
            if(padding_number % 4 != 0)
            {
                char padding[] = "";
                for(int i = 0 ; i< (4 - padding_number % 4); i ++)
                    Databuff.add_buff(padding,sizeof(padding));
            }
        }
        else if(session_type == NORMAL)
        {
            login_rsp_hdr.sid.id.tsih = 6;
            char key_value9[] = "TargetPortalGroupTag=1";
            Databuff.add_buff(key_value9,sizeof(key_value9));
            char key_value10[] = "HeaderDigest=None";
            Databuff.add_buff(key_value10,sizeof(key_value10));
            char key_value11[] = "DataDigest=None";
            Databuff.add_buff(key_value11,sizeof(key_value11));
            char key_value12[] = "DefaultTime2Wait=2";
            Databuff.add_buff(key_value12,sizeof(key_value12));
            char key_value13[] = "DefaultTime2Retain=0";
            Databuff.add_buff(key_value13,sizeof(key_value13));
            char key_value14[] = "IFMarker=No";
            Databuff.add_buff(key_value14,sizeof(key_value14));
            char key_value15[] = "OFMarker=No";
            Databuff.add_buff(key_value15,sizeof(key_value15));
            char key_value16[] = "ErrorRecoveryLevel=0";
            Databuff.add_buff(key_value16,sizeof(key_value16));
            char key_value17[] = "InitialR2T=Yes";
            Databuff.add_buff(key_value17,sizeof(key_value17));
            char key_value18[] = "ImmediateData=Yes";
            Databuff.add_buff(key_value18,sizeof(key_value18));
            char key_value19[] = "MaxBurstLength=262144";
            Databuff.add_buff(key_value19,sizeof(key_value19));
            char key_value20[] = "FirstBurstLength=65536";
            Databuff.add_buff(key_value20,sizeof(key_value20));
            char key_value21[] = "MaxOutstandingR2T=1";
            Databuff.add_buff(key_value21,sizeof(key_value21));
            char key_value22[] = "MaxConnections=1";
            Databuff.add_buff(key_value22,sizeof(key_value22));
            char key_value23[] = "DataPDUInOrder=Yes";
            Databuff.add_buff(key_value23,sizeof(key_value23));
            char key_value24[] = "DataSequenceInOrder=Yes";
            Databuff.add_buff(key_value24,sizeof(key_value24));
            char key_value25[] = "MaxRecvDataSegmentLength=32768";
            Databuff.add_buff(key_value25,sizeof(key_value25));
           /* char padding[] = "";
            Databuff.add_buff(padding,sizeof(padding));*/
            int n_datalen = htonl(Databuff.buff_length );
            unsigned char datalen[4];
            memcpy(datalen,&n_datalen,sizeof(int));
            memcpy(&(login_rsp_hdr.datalength),&datalen[1],3);
            padding_number = Databuff.buff_length;

            if(padding_number % 4 != 0)
            {
                char padding[] = "";
                for(int i = 0 ; i< (4 - padding_number % 4); i ++)
                    Databuff.add_buff(padding,sizeof(padding));
            }
        }
        BHSbuff.delete_buff();
        BHSbuff.add_buff(&login_rsp_hdr, BHS_LEN);

        i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
        i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
        return 0;
}

int I_Manager_Agent::cmnd_exec_text()
{
    text_req_hdr = (struct iscsi_text_req_hdr*)pdu.bhs;
    text_rsp_hdr.opcode = ISCSI_OP_TEXT_RSP;
    text_rsp_hdr.flag = text_req_hdr->flag;
    text_rsp_hdr.ahslength = 0;

    text_rsp_hdr.itt = text_req_hdr->itt;
    text_rsp_hdr.ttt = text_req_hdr->ttt;

    text_rsp_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(text_req_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(text_req_hdr->cmd_sn);

    text_rsp_hdr.exp_cmd_sn =htonl( max_cmd_sn + 1);
    text_rsp_hdr.max_cmd_sn =htonl( max_cmd_sn + 2);


    Databuff.delete_buff();
    char key_value1[] = "TargetName=iqn.2001-04.com.example:storage.disk2.sys1.xyz";
    Databuff.add_buff(key_value1,sizeof(key_value1));
    char key_value2[] = "TargetAddress=192.168.1.65:3260,1";
    Databuff.add_buff(key_value2,sizeof(key_value2));

    int n_datalen = htonl(Databuff.buff_length);
    unsigned char datalen[4];
    memcpy(datalen,&n_datalen,sizeof(int));
    memcpy(&(text_rsp_hdr.datalength),&datalen[1],3);

    BHSbuff.delete_buff();
    BHSbuff.add_buff(&(text_rsp_hdr),BHS_LEN);
    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
    i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
    return 0;
}

int I_Manager_Agent::cmnd_exec_dataout()
{
    data_out_hdr = (struct iscsi_data_out_hdr*)pdu.bhs;
    
    if(d_manager_agent.data_out_cmnd(data_out_hdr,&Databuff) < 0)
    {
        cout << "d_manager_agent.read_cmnd error"<< endl;
        return -1;
    }
    else
        return 0;

}

int I_Manager_Agent::cmnd_exec_logout()
{
    logout_req_hdr = (struct iscsi_logout_req_hdr*)pdu.bhs;
    logout_rsp_hdr.opcode = ISCSI_OP_LOGOUT_RSP;
    logout_rsp_hdr.flag = 0x80;
    logout_rsp_hdr.response = 0x00;
    logout_rsp_hdr.ahslength = 0;
    memset(logout_rsp_hdr.datalength,'\0',3);
    logout_rsp_hdr.itt = logout_req_hdr -> itt;

    logout_rsp_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(logout_req_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(logout_req_hdr->cmd_sn);

    logout_rsp_hdr.exp_cmd_sn = htonl(max_cmd_sn);
    logout_rsp_hdr.max_cmd_sn = htonl(max_cmd_sn + 32);
    logout_rsp_hdr.time2wait = 0;
    logout_rsp_hdr.time2retain = 0;

    Databuff.delete_buff();
    BHSbuff.delete_buff();
    BHSbuff.add_buff(&logout_rsp_hdr,BHS_LEN);

    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
    return 0;
}
int I_Manager_Agent::cmnd_exec_nop_out()
{
    nop_out_hdr =(struct iscsi_nop_out_hdr*)pdu.bhs;
    nop_in_hdr.opcode = ISCSI_OP_NOP_IN;
    nop_in_hdr.flag = 0x80;
    nop_in_hdr.ahslength = 0;

    nop_in_hdr.itt = nop_out_hdr->itt;
    nop_in_hdr.ttt = nop_out_hdr->ttt;

    nop_in_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(nop_out_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(nop_out_hdr->cmd_sn);

    nop_in_hdr.exp_cmd_sn = htonl(max_cmd_sn);
    nop_in_hdr.max_cmd_sn = htonl(max_cmd_sn);

    Databuff.delete_buff();
    BHSbuff.delete_buff();
    BHSbuff.add_buff(&nop_in_hdr,BHS_LEN);
    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
    return 0;
}

int I_Manager_Agent::cmnd_exec_scsi()
{
    scsi_cmd_hdr = (struct iscsi_scsi_cmd_hdr*)pdu.bhs;
   switch(scsi_cmd_hdr -> scb[0])
   {
       case SCSI_OP_REPORT_LUN:
           if( scsi_cmnd_exec_report() < 0)
           {
                cout << "scsi_cmnd_exec_report error"<< endl;
                return -1;
           }
           else
               return 0;
       case SCSI_OP_INQUIRY_LUN:
           if(scsi_cmnd_exec_inquiry() < 0)
           {
            cout << "scsi_cmnd_exec_inquiry error"<< endl;
           }
           else
               return 0;
       case SCSI_OP_READ_CAPACITY:
           if(scsi_cmnd_exec_read_capacity() < 0)
           {
                cout << "scsi_cmnd_exec_read_capacity error"<< endl;
           }
           else
               return 0;
       case SCSI_OP_MODE_SENSE:
           if(scsi_cmnd_exec_mode_sense() < 0)
           {
                cout << "scsi_cmnd_exec_mode_sense"<<endl;
           }
           else
               return 0;
       case SCSI_OP_READ10:
           if(scsi_cmnd_exec_read10() < 0)
           {
                cout << "scsi_cmnd_exec_read10"<<endl;
           }
           else
               return 0;
       case SCSI_OP_WRITE10:
           if(scsi_cmnd_exec_write10() < 0)
           {
                cout << "scsi_cmnd_exec_write10"<<endl;
           }
           else
               return 0;
       case SCSI_OP_TEST:
           if(scsi_cmnd_exec_test() < 0)
           {
                cout << "scsi_cmnd_exec_test error"<< endl;
           }
           else
               return 0;
   }
}

int I_Manager_Agent::scsi_cmnd_exec_report()
{

    reportlun_cmd = (struct scsi_reportlun*)scsi_cmd_hdr->scb;
    data_in_hdr.opcode = ISCSI_OP_DATAIN_RSP;
    data_in_hdr.flag = 0x83;
    data_in_hdr.cmd_status = 0x00;
    data_in_hdr.ahslength = 0;

    data_in_hdr.itt = scsi_cmd_hdr->itt;
    data_in_hdr.ttt = 0xffffffff;

    data_in_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(scsi_cmd_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(scsi_cmd_hdr->cmd_sn);

    data_in_hdr.exp_cmd_sn = htonl(max_cmd_sn + 1);
    data_in_hdr.max_cmd_sn = htonl(max_cmd_sn + 33);
    data_in_hdr.data_sn = 0;
    data_in_hdr.buffer_offset = 0;
   // data_in_hdr.residual_count = (ntohl(reportlun_cmd -> allocation_length) - 16 );
    data_in_hdr.residual_count = htonl(0x00000ff0);

    reportlun_rsp.lun_list_length = htonl(8);
    reportlun_rsp.firstlun = 0;

    Databuff.delete_buff();
    Databuff.add_buff(&reportlun_rsp,16);

    int n_datalen = htonl(Databuff.buff_length);
    unsigned char datalen[4];
    memcpy(datalen,&n_datalen,sizeof(int));
    memcpy(&(data_in_hdr.datalength), &datalen[1], 3);

    BHSbuff.delete_buff();
    BHSbuff.add_buff(&(data_in_hdr), BHS_LEN);

    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
    i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
    return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_inquiry()
{
    int n_datalen;
    unsigned char datalen[4];
    int alloca_length;

    inquirylun_cmd = (struct scsi_inquirylun*)scsi_cmd_hdr->scb;
    data_in_hdr.opcode = ISCSI_OP_DATAIN_RSP;
    data_in_hdr.cmd_status = 0x00;
    data_in_hdr.ahslength = 0;

    data_in_hdr.itt = scsi_cmd_hdr->itt;
    data_in_hdr.ttt = 0xffffffff;

    data_in_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(scsi_cmd_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(scsi_cmd_hdr->cmd_sn);

    data_in_hdr.exp_cmd_sn = htonl(max_cmd_sn + 1);
    data_in_hdr.max_cmd_sn = htonl(max_cmd_sn + 33);
    data_in_hdr.data_sn = 0;
    data_in_hdr.buffer_offset = 0;

    switch(inquirylun_cmd->flag)
    {
        case 0x00:
            data_in_hdr.flag = 0x81;

            inquirylunall_rsp.flag1 = 0;
            inquirylunall_rsp.flag2 = 0;
            inquirylunall_rsp.version = 0x04;
            inquirylunall_rsp.flag3 = 0x52;
            inquirylunall_rsp.additional_length = 0x3b;
            inquirylunall_rsp.flag4 = 0;
            inquirylunall_rsp.flag5 = 0;
            inquirylunall_rsp.flag6 =0x02;
            strncpy(inquirylunall_rsp.vendor_identification,"IET     ",8);
            strncpy(inquirylunall_rsp.product_identification,"VIRTUAL-DISK    ",16);
            strncpy(inquirylunall_rsp.product_revision_level,"0   ",4);
            memset(inquirylunall_rsp.vendor_specific,0,20);
            inquirylunall_rsp.version_descriptor1 = htons(0x0320);
            inquirylunall_rsp.version_descriptor2 = htons(0x0960);
            inquirylunall_rsp.version_descriptor3 = htons(0x0300);

            alloca_length = inquirylun_cmd -> allocation_length;
            if(alloca_length > 64)
            {
                data_in_hdr.residual_count = htonl(alloca_length - 64);
                Databuff.delete_buff();
                Databuff.add_buff(&inquirylunall_rsp,64);
            }
            else
            {
                data_in_hdr.residual_count = 0;
                Databuff.delete_buff();
                Databuff.add_buff(&inquirylunall_rsp,alloca_length);
            }


            n_datalen= htonl(Databuff.buff_length);
            memcpy(datalen,&n_datalen,sizeof(int));
            memcpy(&(data_in_hdr.datalength), &datalen[1], 3);
            

            BHSbuff.delete_buff();
            BHSbuff.add_buff(&(data_in_hdr), BHS_LEN);

            i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
            i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
            return 0;
        case 0x01:
            switch(inquirylun_cmd->page_operationcode)
            {
                case 0x00:
                    data_in_hdr.flag = 0x83;
                    data_in_hdr.residual_count = htonl(0x000000f7);

                    inquirylun00_rsp.flag1 = 0x00;
                    inquirylun00_rsp.pagecode = 0x00;
                    inquirylun00_rsp.page_length = 0x03;
                    inquirylun00_rsp.firstpagecode = 0x00;
                    inquirylun00_rsp.secondpagecode = 0x80;
                    inquirylun00_rsp.thirdpagecode = 0x83;
                    
                    Databuff.delete_buff();
                    Databuff.add_buff(&inquirylun00_rsp,8);

                    n_datalen= htonl(Databuff.buff_length - 1);
                    memcpy(datalen,&n_datalen,sizeof(int));
                    memcpy(&(data_in_hdr.datalength), &datalen[1], 3);

                    BHSbuff.delete_buff();
                    BHSbuff.add_buff(&(data_in_hdr), BHS_LEN);

                    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
                    i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
                    break;
                case 0x83:
                    
                    data_in_hdr.flag = 0x83;
                    data_in_hdr.residual_count = htonl(0x000000dd);

                    inquirylun83_rsp.flag1 = 0x00;
                    inquirylun83_rsp.pagecode = 0x83;
                    inquirylun83_rsp.page_length = 0x1c;
                    inquirylun83_rsp.flag2 = 0x01;
                    inquirylun83_rsp.flag3 = 0x01;
                    inquirylun83_rsp.identifier_length = 0x18;
                    
                    char id[inquirylun83_rsp.identifier_length];
                    memset(id,'\0',inquirylun83_rsp.identifier_length);
                    strncpy(id,"IET",3);
                    strncpy(id+8,"xyz",3);
                    inquirylun83_rsp.identifier = id;

                    Databuff.delete_buff();
                    Databuff.add_buff(&inquirylun83_rsp,8 );
                    Databuff.add_buff(inquirylun83_rsp.identifier,inquirylun83_rsp.identifier_length);

                    n_datalen = htonl(Databuff.buff_length);
                    memcpy(datalen,&n_datalen,sizeof(int));
                    memcpy(&(data_in_hdr.datalength), &datalen[1], 3);

                    BHSbuff.delete_buff();
                    BHSbuff.add_buff(&(data_in_hdr),BHS_LEN);

                    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
                    i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
                    break;
                case 0x80:

                    data_in_hdr.flag = 0x83;
                    data_in_hdr.residual_count = htonl(0x000000ea);

                    inquirylun80_rsp.flag1 = 0x00;
                    inquirylun80_rsp.pagecode = 0x80;
                    inquirylun80_rsp.page_length = 0x10;

                    char s_number[inquirylun80_rsp.page_length];
                    strncpy(s_number,"             xyz",16);

                    Databuff.delete_buff();
                    Databuff.add_buff(&inquirylun80_rsp,4);
                    Databuff.add_buff(s_number,inquirylun80_rsp.page_length);
 
                    n_datalen = htonl(Databuff.buff_length);
                    memcpy(datalen,&n_datalen,sizeof(int));
                    memcpy(&(data_in_hdr.datalength), &datalen[1], 3);

                    BHSbuff.delete_buff();
                    BHSbuff.add_buff(&(data_in_hdr),BHS_LEN);

                    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
                    i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
                    break;

            }
            return 0;
    }
    return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_read_capacity()
{
    int n_datalen;
    unsigned char datalen[4];

    data_in_hdr.opcode = ISCSI_OP_DATAIN_RSP;
    data_in_hdr.flag = 0x81;
    data_in_hdr.cmd_status = 0x00;
    data_in_hdr.ahslength = 0;

    data_in_hdr.itt =scsi_cmd_hdr->itt;
    data_in_hdr.ttt =0xffffffff;

    data_in_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(scsi_cmd_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(scsi_cmd_hdr->cmd_sn);

    data_in_hdr.exp_cmd_sn = htonl(max_cmd_sn + 1);
    data_in_hdr.max_cmd_sn = htonl(max_cmd_sn + 33);
    data_in_hdr.data_sn = 0;
    data_in_hdr.buffer_offset = 0;
    data_in_hdr.residual_count = 0;

    readcapacity_rsp.logical_block_address = htonl(DISK_BLOCK_NUMBER - 1);
    readcapacity_rsp.block_length_in_byte = htonl(BLOCK_SIZE);

    Databuff.delete_buff();
    Databuff.add_buff(&readcapacity_rsp,8);

    n_datalen = htonl(Databuff.buff_length);
    memcpy(datalen,&n_datalen,sizeof(int));
    memcpy(&(data_in_hdr.datalength), &datalen[1],3);

    BHSbuff.delete_buff();
    BHSbuff.add_buff(&(data_in_hdr), BHS_LEN);
    
    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
    i_agent->Writebuff.add_buff(Databuff.bufferptr,Databuff.buff_length);
    return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_mode_sense()
{

    int n_datalen;
    unsigned char datalen[4];

    modesense_cmd = (struct scsi_modesense*)scsi_cmd_hdr->scb;
    data_in_hdr.opcode = ISCSI_OP_DATAIN_RSP;
    data_in_hdr.cmd_status = 0x00;
    data_in_hdr.ahslength = 0;

    data_in_hdr.itt = scsi_cmd_hdr->itt;
    data_in_hdr.ttt = 0xffffffff;

    data_in_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(scsi_cmd_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(scsi_cmd_hdr->cmd_sn);

    data_in_hdr.exp_cmd_sn = htonl(max_cmd_sn + 1);
    data_in_hdr.max_cmd_sn = htonl(max_cmd_sn + 33);
    data_in_hdr.data_sn = 0;
    data_in_hdr.buffer_offset = 0;

    switch(modesense_cmd->flag2 & 0x3f)
    {
        int alloca_length;
        case ALL_PAGE:
            alloca_length = modesense_cmd-> allocation_length;
            data_in_hdr.residual_count = htonl(120 - alloca_length);
            if(data_in_hdr.residual_count == 0)
                data_in_hdr.flag = 0x83;
            else
                data_in_hdr.flag = 0x85;

            parameter_header.mode_data_length = 119;
            parameter_header.medium_type = 0x00;
            parameter_header.device_specific_parameter = 0x00;
            parameter_header.block_descriptor_length = 0x08;
            parameter_header.number_of_blocks = htonl(DISK_BLOCK_NUMBER);
            parameter_header.block_length = htonl(BLOCK_SIZE);

            dis_reconnect_page_rsp.pagecode = 0x02;
            dis_reconnect_page_rsp.page_length = 14;
            dis_reconnect_page_rsp.buffer_full_ratio = 128;
            dis_reconnect_page_rsp.buffer_empty_ratio = 128;
            dis_reconnect_page_rsp.bus_inactivity_limit = htons(0x14);
            dis_reconnect_page_rsp.disconnect_time_limit = 0;
            dis_reconnect_page_rsp.connect_time_limit = 0;
            dis_reconnect_page_rsp.maximum_burst_size = 0;
            dis_reconnect_page_rsp.flag = 0;
            dis_reconnect_page_rsp.first_burst_size = 0;

            format_device_mode_page_rsp.pagecode = 0x03;
            format_device_mode_page_rsp.page_length = 22;
            format_device_mode_page_rsp.tracks_per_zone = 0;
            format_device_mode_page_rsp.alternate_sectors_per_zone = 0;
            format_device_mode_page_rsp.alternate_tracks_per_zone = 0;
            format_device_mode_page_rsp.alternate_tracks_per_logical_unit = 0;
            format_device_mode_page_rsp.sectors_per_track = htons(256);
            format_device_mode_page_rsp.data_bytes_per_physical_sector = htons(512);
            format_device_mode_page_rsp.interleave = 0;
            format_device_mode_page_rsp.track_skew_factor = 0;
            format_device_mode_page_rsp.cylinder_skew_factor = 0;
            format_device_mode_page_rsp.flag = 0;

            rigid_disk_geometry_mode_page_rsp.pagecode = 0x04;
            rigid_disk_geometry_mode_page_rsp.page_length = 22;
            rigid_disk_geometry_mode_page_rsp.number_of_cylinder[1] = 0x04;
            rigid_disk_geometry_mode_page_rsp.number_of_heads = 64;
            rigid_disk_geometry_mode_page_rsp.device_step_rate = 0;
            rigid_disk_geometry_mode_page_rsp.medium_totaltion_rate = htons(3000);

            caching_mode_page_rsp.pagecode = 0x08;
            caching_mode_page_rsp.page_length = 18;
            caching_mode_page_rsp.flag1 = 0x10;
            caching_mode_page_rsp.flag2 = 0x00;
            caching_mode_page_rsp.disable_pre_fetch_transfer_length = 0xff;
            caching_mode_page_rsp.minimum_pre_fetch = 0;
            caching_mode_page_rsp.maximum_pre_fetch = 0xff;
            caching_mode_page_rsp.maximum_pre_fetch_ceiling = 0xff;
            caching_mode_page_rsp.flag3 = 0x80;
            caching_mode_page_rsp.number_of_cache_segments = 0x28;

            control_mode_page_rsp.pagecode = 0x0a;
            control_mode_page_rsp.page_length = 10;
            control_mode_page_rsp.flag1 = 0x02;
            control_mode_page_rsp.extended_self_test_completion_time = htons(587);

            exeptions_control_mode_page_rsp.pagecode = 0x1c;
            exeptions_control_mode_page_rsp.page_length = 10;
            exeptions_control_mode_page_rsp.flag1 = 0x08;

            Databuff.delete_buff();
            Databuff.add_buff(&parameter_header,12);
            Databuff.add_buff(&dis_reconnect_page_rsp,16);
            Databuff.add_buff(&format_device_mode_page_rsp,24);
            Databuff.add_buff(&rigid_disk_geometry_mode_page_rsp,24);
            Databuff.add_buff(&caching_mode_page_rsp,20);
            Databuff.add_buff(&control_mode_page_rsp,12);
            Databuff.add_buff(&exeptions_control_mode_page_rsp, 12);

            n_datalen = htonl(alloca_length);
            memcpy(datalen,&n_datalen,sizeof(int));
            memcpy(&(data_in_hdr.datalength),&datalen[1], 3);

            BHSbuff.delete_buff();
            BHSbuff.add_buff(&(data_in_hdr),BHS_LEN);

            i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
            i_agent->Writebuff.add_buff(Databuff.bufferptr,alloca_length);
            break;
        case DISCONNECT_RECONNECT_PAGE:
            cout << "disconnect_reconnect_page"<<endl;
            break;
        case FORMAT_DEVICE_MODE_PAGE:
            cout << "format_device_mode_page"<< endl;
            break;
        case RIGID_DISK_GEOMETRY_MODE_PAGE:
            cout << "rigid_disk_geometry_mode_page"<< endl;
            break;
        case CACHING_PAGE:

            alloca_length = modesense_cmd-> allocation_length;
            data_in_hdr.residual_count = htonl(32 - alloca_length);
            if(data_in_hdr.residual_count == 0)
                data_in_hdr.flag = 0x83;
            else
                data_in_hdr.flag = 0x85;


            parameter_header.mode_data_length = 31;
            parameter_header.medium_type = 0x00;
            parameter_header.device_specific_parameter = 0x00;
            parameter_header.block_descriptor_length = 0x08;
            parameter_header.number_of_blocks = htonl(DISK_BLOCK_NUMBER);
            parameter_header.block_length = htonl(BLOCK_SIZE);

            caching_mode_page_rsp.pagecode = 0x08;
            caching_mode_page_rsp.page_length = 18;
            caching_mode_page_rsp.flag1 = 0x10;
            caching_mode_page_rsp.flag2 = 0x00;
            caching_mode_page_rsp.disable_pre_fetch_transfer_length = 0xff;
            caching_mode_page_rsp.minimum_pre_fetch = 0;
            caching_mode_page_rsp.maximum_pre_fetch = 0xff;
            caching_mode_page_rsp.maximum_pre_fetch_ceiling = 0xff;
            caching_mode_page_rsp.flag3 = 0x80;
            caching_mode_page_rsp.number_of_cache_segments = 0x28;

            Databuff.delete_buff();
            Databuff.add_buff(&parameter_header,12);
            Databuff.add_buff(&caching_mode_page_rsp,20);

            n_datalen = htonl(alloca_length);
            memcpy(datalen,&n_datalen,sizeof(int));
            memcpy(&(data_in_hdr.datalength),&datalen[1], 3);

            BHSbuff.delete_buff();
            BHSbuff.add_buff(&(data_in_hdr),BHS_LEN);

            i_agent->Writebuff.add_buff(BHSbuff.bufferptr, BHS_LEN);
            i_agent->Writebuff.add_buff(Databuff.bufferptr,alloca_length);
            break;
        case CONTROL_PAGE:
            cout << "control_page"<< endl;
            break;
        case EXCEPTION_CONTROL_MODE_PAGE:

            
            alloca_length = modesense_cmd-> allocation_length;
            data_in_hdr.residual_count = htonl(24 - alloca_length);
            if(data_in_hdr.residual_count == 0)
                data_in_hdr.flag = 0x83;
            else
                data_in_hdr.flag = 0x85;

            parameter_header.mode_data_length = 23;
            parameter_header.medium_type = 0x00;
            parameter_header.device_specific_parameter = 0x00;
            parameter_header.block_descriptor_length = 0x08;
            parameter_header.number_of_blocks = htonl(DISK_BLOCK_NUMBER);
            parameter_header.block_length = htonl(BLOCK_SIZE);

            exeptions_control_mode_page_rsp.pagecode = 0x1c;
            exeptions_control_mode_page_rsp.page_length = 10;
            exeptions_control_mode_page_rsp.flag1 = 0x08;

            Databuff.delete_buff();
            Databuff.add_buff(&parameter_header,12);
            Databuff.add_buff(&exeptions_control_mode_page_rsp,12);

            n_datalen = htonl(alloca_length);
            memcpy(datalen,&n_datalen,sizeof(int));
            memcpy(&(data_in_hdr.datalength),&datalen[1], 3);

            BHSbuff.delete_buff();
            BHSbuff.add_buff(&(data_in_hdr),BHS_LEN);

            i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
            i_agent->Writebuff.add_buff(Databuff.bufferptr,alloca_length);
            break;
    }
    return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_read10()
{
    if(d_manager_agent.read_cmnd(scsi_cmd_hdr) < 0)
    {
        cout << "d_manager_agent.read_cmnd error"<< endl;
        return -1;
    }
    else
        return 0;


}

int I_Manager_Agent::continue_data_in()
{
    return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_write10()
{
    if(d_manager_agent.write_cmnd(scsi_cmd_hdr,&Databuff) < 0)
    {
        cout << "d_manager_agent.read_cmnd error"<< endl;
        return -1;
    }
    else
        return 0;
}

int I_Manager_Agent::scsi_cmnd_exec_test()
{
    scsi_rsp_hdr.opcode = 0x21;
    scsi_rsp_hdr.flag = 0x80;
    scsi_rsp_hdr.response = 0x00;
    scsi_rsp_hdr.cmd_status = 0x00;
    scsi_rsp_hdr.ahslength = 0x00;
    scsi_rsp_hdr.itt = scsi_cmd_hdr->itt;

    scsi_rsp_hdr.stat_sn = htonl(sn);
    sn ++;

    if(htonl(scsi_cmd_hdr->cmd_sn) > max_cmd_sn)
        max_cmd_sn = htonl(scsi_cmd_hdr->cmd_sn);

    scsi_rsp_hdr.exp_cmd_sn = htonl(max_cmd_sn + 1);
    scsi_rsp_hdr.max_cmd_sn = htonl(max_cmd_sn + 33);
       
    Databuff.delete_buff();

    BHSbuff.delete_buff();
    BHSbuff.add_buff(&(scsi_rsp_hdr), BHS_LEN);

    i_agent->Writebuff.add_buff(BHSbuff.bufferptr,BHS_LEN);
    return 0;
}


class I_Manager_Agent i_manager_agent;
