# FindMSSQL
Find all MSSQL Server

���� ��Ʈ��ũ���� ��ġ�� MSSQL�� ������ ��ȸ �մϴ�.

Visual Studio 2015 MFC ��ݿ��� �ڵ��� �ý��ϴ�.


## Enveroment
* Virsual Studio 2015 
* MFC (v140)

## How to use

* �Լ� ������ �Ʒ��� �����ϴ�.
* 3��° �Ķ���͸� �����ϸ� ���� ��Ʈ��ũ���� ��� ������ �˻��մϴ�. (Broadcast)

```c++
bool GetMSSQLInfo(CString &info, int timeout_sec, CString ip = _T(""));
```

## How to implement

* MSSQL�� ��ġ�ϸ� SQL Server Browser�� �Բ� ��ġ�˴ϴ�.
* SQL Server Browser �����ؼ� DBMS ������ �����ɴϴ�.
  - UDP 1434 ��Ʈ�� ����
  - Send  0x02

