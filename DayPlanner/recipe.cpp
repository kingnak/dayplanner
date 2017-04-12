#include "recipe.h"

Recipe::Recipe(QObject *parent)
	: QObject(parent),
	  m_recipe(nullptr)
{
	Q_ASSERT(false);
}

Recipe::Recipe(RecipeDAO *recipe, QObject *parent)
	: QObject(parent),
	  m_recipe(recipe)
{

}

Recipe::~Recipe()
{
	delete m_recipe;
}

qint32 Recipe::id() const
{
	return m_recipe->id();
}

QString Recipe::name() const
{
	return m_recipe->name();
}

void Recipe::setName(const QString &n)
{
	if (n != name()) {
		m_recipe->setName(n);
		if (m_recipe->save()) {
			emit nameChanged();
		}
	}
}

qint32 Recipe::quantity() const
{
	return m_recipe->quantity();
}

void Recipe::setQuantity(qint32 q)
{
	if (q != quantity()) {
		m_recipe->setQuantity(q);
		if (m_recipe->save()) {
			emit quantityChanged();
		}
	}
}

qreal Recipe::fat() const
{
	return m_recipe->fat();
}

void Recipe::setFat(qreal f)
{
	if (f != fat()) {
		m_recipe->setFat(f);
		if (m_recipe->save()) {
			emit fatChanged();
		}
	}
}

qreal Recipe::protein() const
{
	return m_recipe->protein();
}

void Recipe::setProtein(qreal p)
{
	if (p != protein()) {
		m_recipe->setProtein(p);
		if (m_recipe->save()) {
			emit proteinChanged();
		}
	}
}

qreal Recipe::carbs() const
{
	return m_recipe->carbs();
}

void Recipe::setCarbs(qreal c)
{
	if (c != carbs()) {
		m_recipe->setCarbs(c);
		if (m_recipe->save()) {
			emit carbsChanged();
		}
	}
}

qreal Recipe::calories() const
{
	return m_recipe->calories();
}

void Recipe::setCalories(qreal c)
{
	if (c != calories()) {
		m_recipe->setCalories(c);
		if (m_recipe->save()) {
			emit caloriesChanged();
		}
	}
}

QString Recipe::url() const
{
	return m_recipe->url();
}

void Recipe::setUrl(const QString &u)
{
	if (u != url()) {
		m_recipe->setUrl(u);
		if (m_recipe->save()) {
			emit urlChanged();
		}
	}
}
