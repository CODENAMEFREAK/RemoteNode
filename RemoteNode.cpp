//============================================================================
// Name        : RemoteNode.cpp
// Author      : Anubhav Guleria
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include<time.h>
#include<unistd.h>
#include <fstream>
#include <libvirt/libvirt.h>
using namespace std;


int migrationNumber;
ofstream outputStream;

/**
    To make Remote connections.
*/
virConnectPtr makeRemoteConnection(char * connectionString)
	{
		virConnectPtr remoteConnection = NULL;
		remoteConnection = virConnectOpen(connectionString);//virConnectOpen is from libvirt.c
		return remoteConnection;
	}

/**
	To get number of active domains.
*/
int getNumberOfActiveDomains(virConnectPtr connection)
	{
		if(connection!=NULL)
		{
			//virConnectNumOfDomains returns number of Active Domains.
			return virConnectNumOfDomains(connection);
		}
		else return -1;
	}

void getDomainsID(virConnectPtr connection, int * domains, int maxNumOfDomains)
	{
		if(connection!=NULL && domains!=NULL)
			virConnectListDomains(connection,domains,maxNumOfDomains);
	}

/**
	To connect to Active Domain with ID.
	*/

virDomainPtr connectToDomainWithID(virConnectPtr connection, int domainID)
	{
		virDomainPtr domPtr = NULL;
		if(connection!=NULL)
			domPtr = virDomainLookupByID(connection,domainID);
		return domPtr;
	}


void printStats(virDomainPtr domainToMigrate)
{
		outputStream.open("StatsCollector",ios::app);
		virDomainJobInfo info;
        virTypedParameterPtr  params= NULL;
        int nparams = 0;
        unsigned int flags =0;
        memset(&info,0,sizeof(info));
        int rc = virDomainGetJobStats(domainToMigrate,&info.type,&params,&nparams,flags);
        if(rc==0)
        {
        	unsigned long long value =0;


        	cout<<"EVENT_MIGRATION_NUMBER:"<<migrationNumber<<endl;
        	outputStream<<"EVENT_MIGRATION_NUMBER:"<<migrationNumber<<endl;
            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_SETUP_TIME,&value);
            //cout<<"Setup time in milliseconds (before any iteration begins) "<<value<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_ITERATION,&value);
            cout<<"VIR_DOMAIN_JOB_MEMORY_ITERATION:"<<value<<endl;
            outputStream<<"VIR_DOMAIN_JOB_MEMORY_ITERATION:"<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_TIME_ELAPSED,&value);
            //cout<<"Time elapsed in milliseconds since the beginning of job "<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_TIME_ELAPSED_NET,&value);
            //cout<<"Time elapsed in milliseconds since the beginning of job NOT including the time required to transfer control flow "<<value<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_TIME_REMAINING,&value);
            cout<<"VIR_DOMAIN_JOB_TIME_REMAINING:"<<value<<endl;
            outputStream<<"VIR_DOMAIN_JOB_TIME_REMAINING:"<<value<<endl;
            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_TOTAL,&value);
            //cout<<"VIR_DOMAIN_JOB_MEMORY_TOTAL "<<value<<endl;


           //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_PROCESSED,&value);
           //cout<<"VIR_DOMAIN_JOB_MEMORY_PROCESSED "<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_REMAINING,&value);
            //cout<<"VIR_DOMAIN_JOB_MEMORY_REMAINING "<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_NORMAL,&value);
            //cout<<"VIR_DOMAIN_JOB_MEMORY_NORMAL "<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_NORMAL_BYTES,&value);
            //cout<<"VIR_DOMAIN_JOB_MEMORY_NORMAL_BYTES "<<value<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_DIRTY_RATE,&value);
            cout<<"VIR_DOMAIN_JOB_MEMORY_DIRTY_RATE:"<<value<<endl;
            outputStream<<"VIR_DOMAIN_JOB_MEMORY_DIRTY_RATE:"<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_CONSTANT,&value);
            //cout<<"VIR_DOMAIN_JOB_MEMORY_CONSTANT "<<value<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_MEMORY_BPS,&value);
            cout<<"VIR_DOMAIN_JOB_MEMORY_BPS:"<<(value*8.0)/(1024*1024)<<endl;
            outputStream<<"VIR_DOMAIN_JOB_MEMORY_BPS:"<<(value*8.0)/(1024*1024)<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_DOWNTIME,&value);
            cout<<"VIR_DOMAIN_JOB_DOWNTIME:"<<value<<endl;
            outputStream<<"VIR_DOMAIN_JOB_DOWNTIME:"<<value<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_DOWNTIME_NET,&value);
            cout<<"VIR_DOMAIN_JOB_DOWNTIME_NET:"<<value<<endl;
            outputStream<<"VIR_DOMAIN_JOB_DOWNTIME_NET:"<<value<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_DATA_TOTAL,&value);
            cout<<"VIR_DOMAIN_JOB_DATA_TOTAL:"<<(value*1.0)/(1024*1024)<<endl;
            outputStream<<"VIR_DOMAIN_JOB_DATA_TOTAL:"<<(value*1.0)/(1024*1024)<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_DATA_PROCESSED,&value);
            cout<<"VIR_DOMAIN_JOB_DATA_PROCESSED:"<<(value*1.0)/(1024*1024)<<endl;
            outputStream<<"VIR_DOMAIN_JOB_DATA_PROCESSED:"<<(value*1.0)/(1024*1024)<<endl;

            virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_DATA_REMAINING,&value);
            cout<<"VIR_DOMAIN_JOB_DATA_REMAINING:"<<(value*1.0)/(1024*1024)<<endl;
            outputStream<<"VIR_DOMAIN_JOB_DATA_REMAINING:"<<(value*1.0)/(1024*1024)<<endl;


            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_COMPRESSION_PAGES,&value);
            //cout<<"VIR_DOMAIN_JOB_COMPRESSION_PAGES "<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_COMPRESSION_OVERFLOW,&value);
            //cout<<"VIR_DOMAIN_JOB_COMPRESSION_OVERFLOW "<<value<<endl;


            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_COMPRESSION_CACHE_MISSES,&value);
            //cout<<"VIR_DOMAIN_JOB_COMPRESSION_CACHE_MISSES "<<value<<endl;

            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_COMPRESSION_CACHE,&value);
            //cout<<"VIR_DOMAIN_JOB_COMPRESSION_CACHE "<<value<<endl;




            //virTypedParamsGetULLong(params,nparams,VIR_DOMAIN_JOB_COMPRESSION_BYTES,&value);
            //cout<<"Number of compressed bytes transferred since the beginning of migration "<<value<<endl;







        }

	}
/**
 * Give stats about incoming Migration.
 * TODO: Check if can it be executed on same as source.
 * **/
int main() {

	//remoteNodeName  = "qemu+ssh://csuser@10.112.19.129/system"
	char * remoteNodeName ="qemu+ssh://csuser@10.112.19.129/system";
	migrationNumber = -1;
	unsigned int snapShotDelay = 10;
	cout<<"Stats Collecter Initiated\n\t[Sampling after "<<snapShotDelay<<" ]"<<endl;
	virConnectPtr remoteNode = makeRemoteConnection(remoteNodeName);
	if(remoteNode==NULL)
			{
				cout<<"Failed to Connect"<<endl;
				return EXIT_FAILURE;
			}
	else{
	int numOfDomainsOnRemote = getNumberOfActiveDomains(remoteNode);
	bool isInitialized =false;
	virDomainPtr domainToMigrate = NULL;

	while(true)
	{
		if(numOfDomainsOnRemote==1)
		{
			if(!isInitialized)
			{
				int *domains = (int *)malloc(sizeof(int)*numOfDomainsOnRemote);
				getDomainsID(remoteNode,domains,numOfDomainsOnRemote);
				domainToMigrate = connectToDomainWithID(remoteNode,domains[0]);
				free(domains);
				isInitialized =true;
				migrationNumber+=2;
				 cout<<"Migration_Number:\t"<<migrationNumber<<endl;

			}
			//i.e. there is a node on remote
			printStats(domainToMigrate);
			sleep(snapShotDelay);
			numOfDomainsOnRemote = getNumberOfActiveDomains(remoteNode);
		}
		else{
		numOfDomainsOnRemote = getNumberOfActiveDomains(remoteNode);
		isInitialized =false;
		}
	}
	}
	return EXIT_SUCCESS;
}




