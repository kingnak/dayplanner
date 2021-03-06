#include "daobase.h"


bool DAOBase::save()
{
    if (m_state == New) {
        if (doInsert()) {
            m_state = Existing;
            return true;
        }
        return false;
    } else {
        return doUpdate();
    }
}

bool DAOBase::load()
{
    if (doLoad()) {
        m_state = Existing;
        return true;
    } else {
        doReset();
        return false;
    }
}

bool DAOBase::remove()
{
    if (m_state == New) {
        return doReset();
    } else {
        if (doRemove()) {
            m_state = New;
            return true;
        }
        return false;
    }
}

DAOBase::State DAOBase::state() const
{
    return m_state;
}
