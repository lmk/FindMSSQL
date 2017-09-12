# FindMSSQL
Find all MSSQL Server

같은 네트워크망에 설치된 MSSQL의 정보를 조회 합니다.

Visual Studio 2015 MFC 기반에서 코딩해 봤습니다.


## Enveroment
* Virsual Studio 2015 
* MFC (v140)

## How to use

* 함수 원형은 아래와 같습니다.
* 3번째 파라미터를 생략하면 같은 네트워크망의 모든 서버를 검색합니다. (Broadcast)

```c++
bool GetMSSQLInfo(CString &info, int timeout_sec, CString ip = _T(""));
```

## How to implement

* MSSQL을 설치하면 SQL Server Browser가 함께 설치됩니다.
* SQL Server Browser 접속해서 DBMS 정보를 가져옵니다.
  - UDP 1434 포트에 접속
  - Send  0x02

