//
#include "pch.h"
//#include "AWS.h"
//#include <iostream>
//#include <libpq-fe.h>
//#include <string>
//#include <fstream>
//#include <aws/core/Aws.h>
//#include <aws/s3/S3Client.h>
//#include <aws/s3/model/GetObjectRequest.h>
//#include <aws/s3/model/PutObjectRequest.h>
//
//using namespace std;
//using namespace Aws;
//using namespace Aws::Client;
//using namespace Aws::S3;
//using namespace Aws::S3::Model;
//
//AWS::AWS() : m_clientConfig(ClientConfiguration())
//{
//    m_clientConfig.region = "ap-northeast-2";
//}
//
////AWS::AWS(const String& region) : m_clientConfig(ClientConfiguration()), m_region(region) {
////    m_clientConfig.region = m_region;
////}
//
//AWS::~AWS()
//{
//}
//
//// ������ ���� �Լ�
//bool AWS::RDSinsertData(const char* columnname, const char* inputData, const char* tablename)
//{
//    string insert_query = "INSERT INTO public." + string(tablename) + " (" + string(columnname) + ") VALUES " + string(inputData);
//    //  string insert_query = "INSERT INTO public.thing (id, username, password) VALUES ('3', 'c', '1234')";
//    PGresult* res = PQexec(conn, insert_query.c_str());
//    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
//        cerr << "Insertion failed: " << PQerrorMessage(conn) << endl;
//        return false;
//    }
//    PQclear(res);
//    return true;
//}
//// ������ ��� �Լ�
//bool AWS::RDSselectData(const char* whatGet, const char* whereData)
//{
//    string select_query = "SELECT " + string(whatGet) + " FROM " + string(whereData);
//    //  string select_query = "SELECT * FROM thing";
//
//    PGresult* res = PQexec(conn, select_query.c_str());
//    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
//        int rows = PQntuples(res);
//        int columns = PQnfields(res); // ������ ���� ��
//        for (int i = 0; i < rows; ++i) {
//            // ���� ������ ���� ����ŭ�� ���
//            for (int j = 0; j < columns; ++j) {
//                cout << PQgetvalue(res, i, j) << "\t";
//            }
//            cout << endl;
//        }
//    }
//    else {
//        cerr << "Selection failed: " << PQerrorMessage(conn) << endl;
//        return false;
//    }
//    PQclear(res);
//    return true;
//}
//
//// ������ ���� �Լ�
//bool AWS::RDSupdateData(const char* columnname, const char* reviseData, const char* id, const char* standard_columnname, const char* tablename)
//{
//    string update_query = "UPDATE public." + string(tablename) + " SET " + string(columnname) + " = \'" + string(reviseData) + "\' WHERE " + string(standard_columnname) + " = \'" + string(id) + "\'";
//    //  string update_query = "UPDATE public.thing SET color = 'r' WHERE id = '1'";
//
//    PGresult* res = PQexec(conn, update_query.c_str());
//
//    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
//        cerr << "Update failed: " << PQerrorMessage(conn) << endl;
//        return false;
//    }
//    PQclear(res);
//
//    return true;
//}
//
//// ������ ���� �Լ�
//bool AWS::RDSdeleteData(const char* columnname, const char* deleteline, const char* tablename)
//{
//    string delete_query = "DELETE FROM public." + string(tablename) + " WHERE " + string(columnname) + " = " + string(deleteline);
//    //  string delete_query = "DELETE FROM public.thing WHERE id = '1'";
//
//    PGresult* res = PQexec(conn, delete_query.c_str());
//    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
//        cerr << "Deletion failed: " << PQerrorMessage(conn) << endl;
//        return false;
//    }
//    PQclear(res);
//    return true;
//}
//
//// ������ ���� Ȯ�� �Լ�
//bool AWS::RDScheckDataExists(const char* columnname, const char* findwhat, const char* tablename)
//{
//    string select_query = "SELECT EXISTS (SELECT 1 FROM " + string(tablename) + " WHERE " + string(columnname) + " = \'" + string(findwhat) + "\')";
//    //  string select_query = "SELECT EXISTS (SELECT 1 FROM thing WHERE color = 'a')";
//
//    PGresult* res = PQexec(conn, select_query.c_str());
//    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
//        if (PQntuples(res) == 1) {
//            // ù ��° ���� ù ��° ���� ���� ������ (����� boolean ����)
//            bool exists = (PQgetvalue(res, 0, 0)[0] == 't'); // 't'�� true, 'f'�� false
//            PQclear(res);
//            return exists;
//        }
//    }
//    PQclear(res);
//    return false;
//}
//
//// S3 ������ ���� �Լ�
//bool AWS::RDSinserts3Data(const char* dataname)
//{
//    string select_query = "SELECT id FROM (SELECT * FROM thing ORDER BY id DESC LIMIT 1)";
//    //  string select_query = "SELECT * FROM thing";
//
//    PGresult* res1 = PQexec(conn, select_query.c_str());
//
//    if (PQresultStatus(res1) == PGRES_TUPLES_OK) {
//
//        string insert_query = "INSERT INTO public.s3data (id,url) VALUES (" + string(PQgetvalue(res1,0,0)) + ",'https://box-s3-buket.s3.ap-northeast-2.amazonaws.com/" + string(dataname) + "')";
//        //  string insert_query = "INSERT INTO public.thing (id, username, password) VALUES ('3', 'c', '1234')";
//        PGresult* res = PQexec(conn, insert_query.c_str());
//        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
//            cerr << "Insertion failed: " << PQerrorMessage(conn) << endl;
//            return false;
//        }
//        PQclear(res);
//    }
//    PQclear(res1);
//
//    return true;
//}
//
//// ������ ���̺� ���� �Լ�
//bool AWS::RDSjoinData()
//{
//
//    string join_query = "SELECT a.id, a.color, a.faulty, b.url FROM thing AS a LEFT OUTER JOIN s3data AS b ON a.id = b.id";
//
//    PGresult* res = PQexec(conn, join_query.c_str());
//
//    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
//        int rows = PQntuples(res);
//        int columns = PQnfields(res); // ������ ���� ��
//        for (int i = 0; i < rows; ++i) {
//            // ���� ������ ���� ����ŭ�� ���
//            for (int j = 0; j < columns; ++j) {
//                cout << PQgetvalue(res, i, j) << "\t";
//            }
//            cout << endl;
//        }
//    }
//    else {
//        cerr << "Selection failed: " << PQerrorMessage(conn) << endl;
//        return false;
//    }
//
//    PQclear(res);
//
//    return true;
//}
//
//// ���� Ȯ�� �Լ�
//bool AWS::RDSckeckConnection()
//{
//    // ���� ���� ���� Ȯ��
//    if (PQstatus(conn) != CONNECTION_OK) {
//        cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
//        PQfinish(conn); // ���� ����
//        return false;
//    }
//    else {
//        cout << "Connected to database" << endl;
//        return true;
//    }
//}
//
//// ���� ���� �Լ�
//void AWS::RDSconnectionEnd()
//{
//    // ���� ����
//    PQfinish(conn);
//}
//
//// S3���� �Լ�
//bool AWS::JoinS3()
//{
//    m_clientConfig.region = "ap-northeast-2";
//
//    return true;
//}
//
//// ������Ʈ �߰� �Լ�
//bool AWS::PutObject(const String& fileName)
//{
//    S3Client s3_client(m_clientConfig);// S3 Ŭ���̾�Ʈ ����
//
//    // ������Ʈ �߰� ��û ����
//    PutObjectRequest request;
//    request.SetBucket(bucketName);
//    request.SetKey(fileName);
//
//    // ���� �Է� ��Ʈ�� ����
//    shared_ptr<IOStream> inputData =
//        MakeShared<FStream>("SampleAllocationTag",
//            fileName.c_str(),
//            std::ios_base::in | std::ios_base::binary);
//
//    // ���� �б� ���� ó��
//    if (!*inputData) {
//        cerr << "Error unable to read file " << fileName << endl;
//        AfxMessageBox(_T("ERROR file"));
//        return false;
//    }
//
//    // ��û�� ���� ������ ����
//    request.SetBody(inputData);
//
//    // ������Ʈ �߰� ��û ����
//    PutObjectOutcome outcome =
//        s3_client.PutObject(request);
//
//    // ������Ʈ �߰� ��� ó��
//    if (!outcome.IsSuccess()) {
//        cerr << "Error: PutObject: " <<
//            outcome.GetError().GetMessage() << endl;
//        AfxMessageBox(_T("ERROR PUT"));
//        return false;
//    }
//    else {
//        cout << "Added object '" << fileName << "' to bucket '"
//            << bucketName << "'." << endl;
//    }
//
//    return outcome.IsSuccess();
//}
//
//// ������Ʈ �������� �Լ�
//bool AWS::GetObject(const String& objectKey)
//{
//    S3Client client(m_clientConfig);// S3 Ŭ���̾�Ʈ ����
//
//    // ������Ʈ �������� ��û ����
//    GetObjectRequest request;
//    request.SetBucket(bucketName);
//    request.SetKey(objectKey);
//
//    // ������Ʈ �������� ��û ����
//    GetObjectOutcome outcome =
//        client.GetObject(request);
//
//    // ������Ʈ �������� ��� ó��
//    if (!outcome.IsSuccess()) {
//        const S3Error& err = outcome.GetError();
//        cerr << "Error: GetObject: " <<
//            err.GetExceptionName() << ": " << err.GetMessage() << endl;
//        return false;
//    }
//    //else {
//    //    ofstream outFile(objectKey.c_str(), ios::binary);// ���� ��� ��Ʈ�� ����
//    //    if (!outFile)
//    //    {
//    //        cerr << "Failed to open file for writing" << endl;
//    //        return false;
//    //    }
//
//    //    // ������Ʈ ������ ���Ϸ� ����
//    //    outFile << outcome.GetResult().GetBody().rdbuf();
//    //    outFile.close();
//
//    //    cout << "Successfully retrieved '" << objectKey << "' from '"
//    //        << bucketName << "'." << endl;
//    //}
//
//    return outcome.IsSuccess();
//
//}
//
////�ѹ��� ��� ���̺� ������ �ø���
//void AWS::Allinput(
//    const char* columnname,
//    const char* inputData,
//    const String& fileName,
//    const char* tablename
//)
//{
//    RDSinsertData(columnname, inputData, tablename);
//    PutObject(fileName.c_str());
//    RDSinserts3Data(fileName.c_str());
//
//}
//
////�ѹ��� ��� ���̺��� ���ϴ� �� ������ �����
//void AWS::AlldeleteData(const char* deleteline, const char* columnname, const char* tablename, const char* tablename2)
//{
//    RDSdeleteData(columnname, deleteline, tablename);
//    RDSdeleteData(columnname, deleteline, tablename2);
//}
//
//// S3 ���� ���� �Լ�
//void AWS::S3connectionEnd() {
//    ShutdownAPI(options);
//}
