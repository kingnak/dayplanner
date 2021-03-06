#ifndef DBDAOBASE_H
#define DBDAOBASE_H

#include "../daobase.h"
#include <QSqlRecord>
#include <QSqlField>

class DataBase;

class DbDAOBase : public virtual DAOBase
{
public:
    DbDAOBase(DataBase *db, DAOBase::State s = DAOBase::New);

protected:
    template<typename T>
    T data(const QString &name) const;
    template<typename T>
    T data(const QString &name, const T &def) const;

    template<typename T>
    void setData(const QString &name, const T &t);

protected:
    static QString escapeTable(const QString &table);
    static QString escapeField(const QString &field);
    static QString escapeValue(QString value);

    // DAOBase implementation
    virtual bool doReset();
    virtual bool doLoad();
    virtual bool doInsert();
    virtual bool doUpdate();
    virtual bool doRemove();

    // Should be overridden by subclass if using custom queries
    virtual QString loadQuery();
    virtual QString insertQuery();
    virtual QString updateQuery();
    virtual QString deleteQuery();

    // Must be overriden by subclass for default queries
    virtual QStringList keyFields();
    virtual QString keyData(const QString &field);
    virtual QStringList orderFields();
    virtual QString tableName();
	virtual QStringList excludeDataFields();

protected:
    QString keyCondition();

protected:
    DataBase *m_db;
    QSqlRecord m_record;
};

template <typename T>
T DbDAOBase::data(const QString &name) const
{
    if (m_record.isEmpty()) {
        return T();
    }
    return qvariant_cast<T> (m_record.value(name));
}

template<typename T>
T DbDAOBase::data(const QString &name, const T &def) const
{
    if (m_record.isEmpty()) {
        return def;
    }
    return qvariant_cast<T> (m_record.value(name));
}

template <typename T>
void DbDAOBase::setData(const QString &name, const T &t)
{
    if (!m_record.contains(name)) {
        m_record.append(QSqlField(name, QVariant::fromValue<T>(t).type()));
    }
    m_record.setValue(name, QVariant::fromValue<T>(t));
}

// Helps preventing MSVC C4250 warning (dominant inheritance)
#define DAO_USE(cls) \
protected: \
    virtual bool doReset() { return cls::doReset(); } \
    virtual bool doLoad() { return cls::doLoad(); } \
    virtual bool doInsert() { return cls::doInsert(); } \
    virtual bool doUpdate() { return cls::doUpdate(); } \
    virtual bool doRemove() { return cls::doRemove(); }

#pragma warning(disable : 4250)

#endif // DBDAOBASE_H
