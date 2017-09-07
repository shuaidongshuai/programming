#include "stdio.h"
#include "mysql.h"  // mysql-devel
#pragma comment(lib, "mysql")   //mysql.dll

int main(int argc, char **argv)
{
	MYSQL * con;
	MYSQL_RES *res;
	MYSQL_ROW row;

	con = mysql_init((MYSQL*)0);  //   111111111111111111111
    mysql_real_connect(con,dbip,dbuser,  dbpasswd,NULL,3306/*TCP IP端口*/,NULL/*Unix Socket  连接类型*/,0/*运行成ODBC数据库标志*/)
    mysql_select_db(con,dbname)
    
    query = "select * from dbuser;";
	mysql_real_query(con,query,strlen(query));    0
    
    res = mysql_store_result(con);//将结果保存在res结构体中
  99:   
 100:      while(row = mysql_fetch_row(res))  
 101:      {  
 102:          /** 
 103:          * MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result); 
 104:           * 检索行 
 105:          */  
 106:   
 107:         for(t=0;t<mysql_num_fields(res);t++)  
 108:          {  
 109:              printf("%s  ",row[t]);  
 110:          }  
 111:          printf(".............\n");  
 113:      }
    
    
  
  // 22222222222222
	if ( con !=NULL && mysql_real_connect(con,dbip,dbuser,  dbpasswd,NULL,3306/*TCP IP端口*/,NULL/*Unix Socket  连接类型*/,0/*运行成ODBC数据库标志*/) )
	{ 

// 33333333333333333333333     user Library;
		 if (!mysql_select_db(con,dbname))
		{ 
				printf("Select successfully the database!\n"); 
	          
				con ->reconnect = 1; 
		
				 query = "set names \'GBK\'";
				rt=mysql_real_query(con,query,strlen(query));
				if (rt)
  54:          {
  55:              printf("Error making query: %s !!!\n",mysql_error(con));
  56:          }
  57:          else
  58:          {
  59:              printf("query %s succeed!\n",query);
  60:          }
  61:          
  62:      }
  63:  }
  64:   
  65:  else
  66:  {
  67:      MessageBoxA(NULL,"Unable to connect the database,check your configuration!","",NULL);
  68:   
  69:  }
  70:   
  71:      //sprintf(tmp,"update %s set 商品=\'%s\',卖出=%d,成交=%d,涨跌=%d,买进=%d,总量=%d,涨幅=%f,时间=\'%s\' where  %s",tablename,goods,sold,deal,fluctuate,buy,total,delta,time,UpdateCon);
  72:      sprintf(tmp,"insert into %s values('%s',%d,%d)",tablename,"null",x,y); //注意如何向具有自增字段的数据库中插入记录
  73:      //MessageBoxA(NULL,tmp,tmp,MB_OK);
  74:      //mysql_query(con,tmp);
  75:   
  ///////////444444444444444444
  76:      rt=mysql_real_query(con,tmp,strlen(tmp));
  77:      if (rt)
  78:      {
  79:          printf("Error making query: %s !!!\n",mysql_error(con));
  80:      }
  81:      else
  82:      {
  83:          printf("%s executed!!!\n",tmp);
  84:      }
  85:      
  86:      sprintf(tmp,"select * from %s",tablename);
  87:      
  88:      rt=mysql_real_query(con,tmp,strlen(tmp));
  89:      if (rt)
  90:      {
  91:          printf("Error making query: %s !!!\n",mysql_error(con));
  92:      } 
  93:      else
  94:      {
  95:          printf("%s executed!!!\n",tmp);
  96:      }
  97:      
  98:      res = mysql_store_result(con);//将结果保存在res结构体中
  99:   
 100:      while(row = mysql_fetch_row(res))  
 101:      {  
 102:          /** 
 103:          * MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result); 
 104:           * 检索行 
 105:          */  
 106:   
 107:         for(t=0;t<mysql_num_fields(res);t++)  
 108:          {  
 109:              printf("%s  ",row[t]);  
 110:          }  
 111:          printf(".............\n");  
 112:          count ++;
 113:      }
 114:     printf("number of rows %d\n",count);
 115:      printf("mysql_free_result...\n");  
 116:      mysql_free_result(res);  
 117:   
 118:      mysql_close(con);
 119:      return 0;
 120:   
 121:  }