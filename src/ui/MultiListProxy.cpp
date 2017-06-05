#include "ui/MultiListProxy.h"
#include<stdio.h>
#include<sstream>
using std::istringstream;
using std::cout;
using std::endl;
AbstractProxy::state MultiListProxy::manipulate(std::string order, AbstractProxy *&new_proxy)
{
    istringstream is(order);
    std::string temp;
    if(is>>temp)
    {
        if(temp=="-r") return AbstractProxy::go_back;//-r ������һ��
        if(temp=="-x") return AbstractProxy::quit;//-x �˳�ϵͳ
        if(temp=="-f") {show(); return AbstractProxy::done;}//ˢ��
        if(temp=="-n")
        {
            int i;
            is>>i;
			PayingEntry *entry=_list->get_vec_entry()[i];
			if(entry!=nullptr) {/*new_proxy=getPayingEntryProxy(entry);return AbstractProxy::new_proxy;*/}
            else return AbstractProxy::fail;
        }
		if(temp=="-s")//-s �������
		{
			map<vector<string>,double> to_pay=_list->get_how_to_pay();
			if(to_pay.size()!=0)
			{
			map<vector<string>,double>::iterator iter;
			for(iter=to_pay.begin();iter!=to_pay.end();iter++) 
			{
				if(iter->second>0)
					cout<<iter->first[0]<<"֧����"<<iter->first[1]<<iter->second<<endl;
				if(iter->second<0)
					cout<<iter->first[1]<<"֧����"<<iter->first[0]<<iter->second<<endl;
			}
			return AbstractProxy::done;
			}
			else 
				return AbstractProxy::fail;
		}
		if(temp=="-p")//-p ��ѯ��֧�����ٻ��߱�֧������
		{
			string name;
			is>>name;
			map<string,double> to_pay=_list->getperson_topaycopy();
			if(to_pay.size()!=0)
			{
			if(to_pay[name]<0)
				cout<<name<<"��Ҫ��֧��"<<to_pay[name]<<endl;
			if(to_pay[name]>0)
				cout<<name<<"��Ҫ֧��"<<to_pay[name]<<endl;
			else
				cout<<name<<"��֧ƽ��"<<endl;
			return AbstractProxy::done;
			}
			else return AbstractProxy::fail;
		}
    }
    return AbstractProxy::fail;
}