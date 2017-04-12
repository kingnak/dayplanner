#ifndef DAOBASE_H
#define DAOBASE_H

class DAOBase
{
public:
    enum State {
        New, Existing
    };

	enum {
		NoItemIndex = 0
	};

    DAOBase(State s = New) : m_state(s) {}
    virtual ~DAOBase() {}

    bool save();
    bool load();
    bool remove();

    State state() const;

protected:
    virtual bool doReset() { return true; }
    virtual bool doLoad() = 0;
    virtual bool doInsert() = 0;
    virtual bool doUpdate() = 0;
    virtual bool doRemove() = 0;

    State m_state;
};

#endif // DAOBASE_H
