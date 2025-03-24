#include "exception.hpp"
#include "chrono.hpp"

asv::chrono::month_day& asv::chrono::month_day::operator+=(month m) noexcept
{
	if (m.get() < 0)
		return this->operator-=(-m);

	int newMonthNumber = (m_month.get() + m.get()) % 12;
	if (newMonthNumber == 0)
		newMonthNumber = 1;

	const int daysLimit = s_daysPerMonth[newMonthNumber - 1];
	if (m_day.get() > daysLimit)
		m_day = day(daysLimit);

	m_month = month(newMonthNumber);

	return *this;
}

asv::chrono::month_day& asv::chrono::month_day::operator-=(month m) noexcept
{
	if (m.get() < 0)
		return this->operator+=(-m);

	int newMonthNumber = (m_month.get() - m.get());
	while (newMonthNumber < 0)
		newMonthNumber += 12;

	const int daysLimit = s_daysPerMonth[newMonthNumber - 1];
	if (m_day.get() > daysLimit)
		m_day = day(daysLimit);

	m_month = month(newMonthNumber);

	return *this;
}

asv::chrono::month_day& asv::chrono::month_day::operator+=(day d) noexcept
{
	if (d.get() < 0)
		return this->operator-=(-d);

	int daysLeftToAdd = d.get();

	while (daysLeftToAdd > 0)
	{
		const int daysRemainingInMonth
			= s_daysPerMonth[m_month.get() - 1] - m_day.get();

		if (daysRemainingInMonth > 0)
		{
			if (daysLeftToAdd >= daysRemainingInMonth)
			{
				int newMonthNumber = m_month.get() + 1;
				if (newMonthNumber > 12)
					newMonthNumber = 1;

				m_month = month(newMonthNumber);
				m_day = day(1);
				daysLeftToAdd -= daysRemainingInMonth + 1;
			}
			else
			{
				m_day += day(daysLeftToAdd);
				daysLeftToAdd = 0;
			}
		}
		else
		{
			int newMonthNumber = m_month.get() + 1;
			if (newMonthNumber > 12)
				newMonthNumber = 1;

			m_month = month(newMonthNumber);
			m_day = day(1);
			--daysLeftToAdd;
		}
	}

	return *this;
}

asv::chrono::month_day& asv::chrono::month_day::operator-=(day d) noexcept
{
	if (d.get() < 0)
		return this->operator+=(-d);

	int daysLeftToSubtract = d.get();

	while (daysLeftToSubtract > 0)
	{
		const int daysRemainingInMonth = m_day.get();

		if (daysLeftToSubtract >= daysRemainingInMonth)
		{
			if (m_month == January)
				m_month = December;
			else
				--m_month;

			daysLeftToSubtract -= daysRemainingInMonth;
			m_day = day(s_daysPerMonth[m_month.get() - 1]);
		}
		else
		{
			m_day -= day(daysLeftToSubtract);
			daysLeftToSubtract = 0;
		}
	}

	return *this;
}

void asv::chrono::month_day::VerifyDate(month m, day d)
{
	const int monthNumber = m.get();

	if ((monthNumber < 1) || (monthNumber > 12))
		throw out_of_range{ "Months must be in range [1, 12]" };

	const int daysLimit = (m == February) ? 29 : s_daysPerMonth[monthNumber - 1];
	const int dayNumber = d.get();

	if ((dayNumber < 1) || (dayNumber > daysLimit))
		throw out_of_range{ "Day is out of range" };
}

asv::chrono::month_day asv::chrono::operator/(month m, day d)
{
	return month_day{ m, d };
}

asv::chrono::month_day_year asv::chrono::operator/(month_day md, year y)
{
	return month_day_year{ md, y };
}

//											 month_day already performs checks on month
void asv::chrono::month_day_year::VerifyDate(month_day md, year y)
{
	const int daysLimit = ((md.m() == February) && IsLeapYear(y))
		? 29 : s_daysPerMonth[md.m().get() - 1];
	const int dayNumber = md.d().get();
	
	if ((dayNumber < 1) || (dayNumber > daysLimit)) //need this check solely for leap days
		throw out_of_range{ "Day is out of range" };
}

void asv::chrono::month_year::VerifyDate(month m, [[maybe_unused]] year y)
{
	if ((m.get() < 1) || (m.get() > 12))
		throw out_of_range{ "Month must be in range [1, 12]" };
}

asv::chrono::month_year asv::chrono::operator/(month m, year y)
{
	return month_year{ m, y };
}

asv::chrono::month_year_day asv::chrono::operator/(month_year my, day d)
{
	return month_year_day{ my, d };
}

asv::chrono::day_month asv::chrono::operator/(day d, month m)
{
	return day_month{ d, m };
}

asv::chrono::day_month_year asv::chrono::operator/(day_month dm, year y)
{
	return day_month_year{ dm, y };
}

asv::chrono::month_day_year& asv::chrono::month_day_year::operator+=(day d) noexcept
{
	if (d.get() < 0)
		return this->operator-=(-d);

	int daysLeftToAdd = d.get();

	while (daysLeftToAdd > 0)
	{
		const month currentMonth = m_monthDay.m();
		const day currentDay = m_monthDay.d();
		const int daysRemainingInMonth
			= (((currentMonth == February) && IsLeapYear(m_year)) ? 29
				: s_daysPerMonth[currentMonth.get() - 1]) - currentDay.get();

		if (daysRemainingInMonth > 0)
		{
			if (daysLeftToAdd >= daysRemainingInMonth)
			{
				int newMonthNumber = currentMonth.get() + 1;
				if (newMonthNumber > 12)
				{
					++m_year;
					newMonthNumber = 1;
				}

				m_monthDay.m(month(newMonthNumber));
				m_monthDay.d(day(1));
				daysLeftToAdd -= daysRemainingInMonth + 1;
			}
			else
			{
				m_monthDay.d(currentDay + day(daysLeftToAdd));
				daysLeftToAdd = 0;
			}
		}
		else
		{
			int newMonthNumber = currentMonth.get() + 1;
			if (newMonthNumber > 12)
			{
				++m_year;
				newMonthNumber = 1;
			}

			m_monthDay.m(month(newMonthNumber));
			m_monthDay.d(day(1));
			--daysLeftToAdd;
		}
	}

	return *this;
}

asv::chrono::month_day_year& asv::chrono::month_day_year::operator-=(day d) noexcept
{
	if (d.get() < 0)
		return this->operator-=(-d);

	int daysLeftToSubtract = d.get();

	while (daysLeftToSubtract > 0)
	{
		const month currentMonth = m_monthDay.m();
		const day currentDay = m_monthDay.d();
		const int daysRemainingInMonth = currentDay.get();

		if (daysLeftToSubtract >= daysRemainingInMonth)
		{
			int newMonthNumber = currentMonth.get() - 1;
			if (newMonthNumber < 1)
			{
				--m_year;
				newMonthNumber = 12;
			}

			const month newMonth(newMonthNumber);
			const int newDayNumber = ((newMonth == February) && IsLeapYear(m_year))
				? 29 : s_daysPerMonth[newMonth.get() - 1];
			const day newDay(newDayNumber);
			m_monthDay = month_day{ newMonth, newDay };
			daysLeftToSubtract -= daysRemainingInMonth;
		}
		else
		{
			m_monthDay.d(currentDay - day(daysLeftToSubtract));
			daysLeftToSubtract = 0;
		}
	}

	return *this;
}

asv::chrono::month_day_year& asv::chrono::month_day_year::operator+=(month m) noexcept
{
	if (m.get() < 0)
		return this->operator-=(-m);

	int newYearNumber = (m_year.get() + m.get() / 12);
	const year newYear(newYearNumber);
	m_year = newYear; //important to do this before the stuff below

	int newMonthNumber = (m_monthDay.m().get() + m.get()) % 12;
	if (newMonthNumber == 0)
		newMonthNumber = 1;

	const month newMonth(newMonthNumber);
	const int daysLimit = ((newMonthNumber == 2) && IsLeapYear(m_year))
		? 29 : s_daysPerMonth[newMonthNumber - 1];
	const day newDay((m_monthDay.d().get() > daysLimit) ? daysLimit
		: m_monthDay.d().get());
	m_monthDay = month_day{ newMonth, newDay };

	return *this;
}

asv::chrono::month_day_year& asv::chrono::month_day_year::operator-=(month m) noexcept
{
	int monthNumber = m_monthDay.m().get(),
		dayNumber = m_monthDay.d().get(),
		yearNumber = m_year.get();

	for (int iter = 0; iter < m.get(); ++iter)
	{
		if (monthNumber == 1)
		{
			monthNumber = 12;
			--yearNumber;
		}
		else
			--monthNumber;
	}

	const month newMonth(monthNumber);
	const year newYear(yearNumber);
	const int daysLimit = ((newMonth == February) && IsLeapYear(newYear))
		? 29 : s_daysPerMonth[newMonth.get() - 1];
	const day newDay((dayNumber > daysLimit) ? daysLimit : dayNumber);

	m_year = newYear;
	m_monthDay = month_day{ newMonth, newDay };

	return *this;
}

asv::chrono::month_day_year& asv::chrono::month_day_year::operator+=(year y) noexcept
{
	m_year += y;

	const int daysLimit = ((m_monthDay.m() == February) && IsLeapYear(m_year))
		? 29 : s_daysPerMonth[m_monthDay.m().get() - 1];
	if (m_monthDay.d().get() > daysLimit)
	{
		const day newDay(daysLimit);
		m_monthDay.d(newDay);
	}

	return *this;
}

asv::chrono::month_day_year& asv::chrono::month_day_year::operator-=(year y) noexcept
{
	m_year -= y;

	const int daysLimit = ((m_monthDay.m() == February) && IsLeapYear(m_year))
		? 29 : s_daysPerMonth[m_monthDay.m().get() - 1];
	if (m_monthDay.d().get() > daysLimit)
	{
		const day newDay(daysLimit);
		m_monthDay.d(newDay);
	}

	return *this;
}

asv::chrono::month_year& asv::chrono::month_year::operator+=(month m) noexcept
{
	if (m.get() < 0)
		return this->operator-=(-m);

	int newMonthNumber = (m_month.get() + m.get()) % 12;
	if (newMonthNumber == 0)
		newMonthNumber = 1;
	m_month = month(newMonthNumber);
	m_year += year(m.get() / 12);

	return *this;
}

asv::chrono::month_year& asv::chrono::month_year::operator-=(month m) noexcept
{
	if (m.get() < 0)
		return this->operator+=(-m);

	int newMonthNumber = (m_month.get() > m.get())
		? (m_month.get() - m.get()) : (12 - (m.get() - m_month.get()));
	m_month = month(newMonthNumber);
	m_year -= year(m.get() / 12);

	return *this;
}

asv::chrono::day_year_month asv::chrono::operator/(day_year dy, month m)
{
	return day_year_month{ dy, m };
}

asv::chrono::year_month asv::chrono::operator/(year y, month m)
{
	return year_month{ y, m };
}

asv::chrono::year_month_day asv::chrono::operator/(year_month ym, day d)
{
	return year_month_day{ ym, d };
}

asv::chrono::year_day_month asv::chrono::operator/(year_day yd, month m)
{
	return year_day_month{ yd, m };
}