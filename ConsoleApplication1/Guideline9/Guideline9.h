#pragma once

class Transaction
{
public:
    virtual void execute() = 0;
};

class Deposit : public Transaction
{
public:
    void execute() override;
};

class Withdrawal : public Transaction
{
public:
    void execute() override;
};

class Transfer : public Transaction
{
public:
    void execute() override;
};

/////////////////////////////////////////////////////////////////
// Gideline9 2-1
class Guidline9_UI_2_1
{
public:
    void requestDepositAmount()
    {
        _deposit.execute();
    }
    void requestWithdrawalAmount()
    {
        _withdrawal.execute();
    }
    void requestTranferAmount()
    {
        _transfer.execute();
    }
    void informaInsufficientFunds();

private:
    Deposit _deposit;
    Withdrawal _withdrawal;
    Transfer _transfer;
};


/////////////////////////////////////////////////////////////////
// Gideline9 2-2
class DepositUI
{
public:
    virtual void requestDepositAmount() = 0;
};

class WithdrawalUI
{
public:
    virtual void requestWithdrawalAmount() = 0;
    virtual void informaInsufficientFunds() = 0;
};

class TransferUI
{
public:
    virtual void requestTranferAmount() = 0;
    virtual void informaInsufficientFunds() = 0;
};


class Guidline9_UI_2_2 : public DepositUI, public WithdrawalUI, public TransferUI
{
public:
    void requestDepositAmount() override
    {
        _deposit.execute();
    }
    void requestWithdrawalAmount() override
    {
        _withdrawal.execute();
    }
    void requestTranferAmount() override
    {
        _transfer.execute();
    }

private:
    Deposit _deposit;
    Withdrawal _withdrawal;
    Transfer _transfer;
};


/////////////////////////////////////////////////////////////////
// Gideline9 2-2 �v���O�C���A�[�L�e�N�`��

//---------------------------
// �Ԉ������

// <thirdparty/Plugin.h>
class Plugin {};

// <thirdparty/VimModePlugin.h>
//#include "thirdparty/Plugin.h"
class VimModePlugin : public Plugin {};

// <yourcode/Editor.h>
//#include "thirdparty/VimModePlugin.h"
class Editor {};

// ������ thirdparty
//   �b     �� Plugin.h ����
//   �b     �� VimModePlugin.h ����
// �@���� yourcode
//          �� Editor.h ���


//---------------------------
// �ˑ��֌W���C��������

// <yourcode/Plugin.h>
class Plugin {};

// <yourcode/Editor.h>
//#include "yourcode/Plugin.h"
class Editor {};

// <thirdparty/VimModePlugin.h>
//#include "yourcode/Plugin.h"
class VimModePlugin : public Plugin {};

// ������ thirdparty
//   �b     �� VimModePlugin.h ����
// �@���� yourcode
//   �@     �� Plugin.h ���
//          �� Editor.h ���
