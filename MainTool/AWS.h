#pragma once
#include <iostream>
#include <libpq-fe.h>
#include <string>

#include <fstream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/DeleteObjectsRequest.h>

using namespace std;
using namespace Aws;
using namespace Aws::Client;
using namespace Aws::S3;
using namespace Aws::S3::Model;

class AWS
{
private:
    // �����ͺ��̽� ���� ���� ����
    const char* conninfo = "host=baxdatabase.clyecqs0oin9.ap-northeast-2.rds.amazonaws.com dbname=boxdata user=boxuser password=qwer1234";
    const String bucketName = "box-s3-buket";
    // PostgreSQL ���� ��ü ����
    PGconn* conn = PQconnectdb(conninfo);

    //s3
    String m_region;// ���� ����
    ClientConfiguration m_clientConfig;// Ŭ���̾�Ʈ ����
    SDKOptions options;// AWS S3 ���� ����� ���� SDK �ʱ�ȭ

public:
	AWS();
	~AWS();

	// RDS
    bool RDSinsertData(const char* columnname, const char* inputData, const char* tablename = "thing");// ������ ���� �Լ�
    bool RDSselectData(const char* whatGet, const char* whereData);// ������ ��� �Լ�
    bool RDSupdateData(const char* columnname, const char* reviseData, const char* id, const char* standard_columnname = "id", const char* tablename = "thing");// ������ ���� �Լ�
    bool RDSdeleteData(const char* columnname, const char* deleteline, const char* tablename = "thing");// ������ ���� �Լ�
    bool RDScheckDataExists(const char* columnname, const char* findwhat, const char* tablename = "thing");// ������ ���� Ȯ�� �Լ�
    bool RDSinserts3Data(const char* dataname);// S3 ������ ���� �Լ�
    vector<vector<string>> AWS::RDSjoinData();// ������ ���̺� ���� �Լ�
    bool RDSckeckConnection();// ���� Ȯ�� �Լ�
    void RDSconnectionEnd();// ���� ���� �Լ�

    //s3
    bool JoinS3();// S3���� �Լ�
    bool PutObject(const String& fileName);// ������Ʈ �߰� �Լ�
    bool GetObject(const String& objectKey);// ������Ʈ �������� �Լ�
    bool DeleteObjects(const std::vector<Aws::String>& objectKey);// ������Ʈ ���� �Լ�
    void S3connectionEnd();// S3 ���� ���� �Լ�

    //�ѹ��� ��� ���̺� ������ �ø���
    void Allinput(const char* columnname, const char* inputData, const String & fileName, const char* tablename = "thing");
    
    //�ѹ��� ��� ���̺��� ���ϴ� �� ������ �����
    void AlldeleteData(const char* deleteline, const char* columnname="id", const char* tablename = "thing", const char* tablename2 = "s3data");
};

