#include "rollinh_lottery_view_private.h"

RollingLotteryViewPrivate::RollingLotteryViewPrivate(RollingLotteryView *ptr)
    : m_status(false)
    , m_statusNum(-1)
    , m_res(-1)
    , m_stopNum(-1)
{
}

RollingLotteryViewPrivate::~RollingLotteryViewPrivate() {}
