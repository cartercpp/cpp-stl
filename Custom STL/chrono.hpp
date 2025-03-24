namespace asv
{
	namespace chrono
	{
		class month
		{
		public:

			//CONSTRUCTORS & STUFF

			constexpr explicit month(int month) noexcept
				: m_month(month)
			{
			}

			//METHODS & STUFF

			constexpr int get() const noexcept
			{
				return m_month;
			}

			constexpr month& operator++() noexcept
			{
				++m_month;
				return *this;
			}

			constexpr month operator++(int) noexcept
			{
				const month output{ *this };
				this->operator++();
				return output;
			}

			constexpr month& operator+=(month m) noexcept
			{
				m_month += m.get();
				return *this;
			}

			constexpr month& operator--() noexcept
			{
				--m_month;
				return *this;
			}

			constexpr month operator--(int) noexcept
			{
				const month output{ *this };
				this->operator--();
				return *this;
			}

			constexpr month& operator-=(month m) noexcept
			{
				m_month -= m.get();
				return *this;
			}

			void swap(month& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend constexpr month operator+(month lArg, month rArg) noexcept
			{
				return lArg += rArg;
			}

			friend constexpr month operator-(month lArg, month rArg) noexcept
			{
				return lArg -= rArg;
			}

			friend constexpr month operator-(month m) noexcept
			{
				return month(-m.m_month);
			}

			friend constexpr bool operator==(month lArg, month rArg) noexcept
			{
				return lArg.m_month == rArg.m_month;
			}

			friend constexpr bool operator!=(month lArg, month rArg) noexcept
			{
				return lArg.m_month != rArg.m_month;
			}

			friend constexpr bool operator<=(month lArg, month rArg) noexcept
			{
				return lArg.m_month <= rArg.m_month;
			}

			friend constexpr bool operator<(month lArg, month rArg) noexcept
			{
				return lArg.m_month < rArg.m_month;
			}

			friend constexpr bool operator>=(month lArg, month rArg) noexcept
			{
				return lArg.m_month >= rArg.m_month;
			}

			friend constexpr bool operator>(month lArg, month rArg) noexcept
			{
				return lArg.m_month > rArg.m_month;
			}

			int m_month;
		};

		inline constexpr month January(1);
		inline constexpr month February(2);
		inline constexpr month March(3);
		inline constexpr month April(4);
		inline constexpr month May(5);
		inline constexpr month June(6);
		inline constexpr month July(7);
		inline constexpr month August(8);
		inline constexpr month September(9);
		inline constexpr month October(10);
		inline constexpr month November(11);
		inline constexpr month December(12);

		class day
		{
		public:

			//CONSTRUCTORS & STUFF

			constexpr explicit day(int day) noexcept
				: m_day(day)
			{
			}

			//METHODS & STUFF

			constexpr int get() const noexcept
			{
				return m_day;
			}

			constexpr day& operator++() noexcept
			{
				++m_day;
				return *this;
			}

			constexpr day operator++(int) noexcept
			{
				const day output{ *this };
				this->operator++();
				return output;
			}

			constexpr day& operator+=(day d) noexcept
			{
				m_day += d.get();
				return *this;
			}

			constexpr day& operator--() noexcept
			{
				--m_day;
				return *this;
			}

			constexpr day operator--(int) noexcept
			{
				const day output{ *this };
				this->operator--();
				return *this;
			}

			constexpr day& operator-=(day d) noexcept
			{
				m_day -= d.get();
				return *this;
			}

			void swap(day& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend constexpr day operator+(day lArg, day rArg) noexcept
			{
				return lArg += rArg;
			}

			friend constexpr day operator-(day lArg, day rArg) noexcept
			{
				return lArg -= rArg;
			}

			friend constexpr day operator-(day m) noexcept
			{
				return day(-m.m_day);
			}

			friend constexpr bool operator==(day lArg, day rArg) noexcept
			{
				return lArg.m_day == rArg.m_day;
			}

			friend constexpr bool operator!=(day lArg, day rArg) noexcept
			{
				return lArg.m_day != rArg.m_day;
			}

			friend constexpr bool operator<=(day lArg, day rArg) noexcept
			{
				return lArg.m_day <= rArg.m_day;
			}

			friend constexpr bool operator<(day lArg, day rArg) noexcept
			{
				return lArg.m_day < rArg.m_day;
			}

			friend constexpr bool operator>=(day lArg, day rArg) noexcept
			{
				return lArg.m_day >= rArg.m_day;
			}

			friend constexpr bool operator>(day lArg, day rArg) noexcept
			{
				return lArg.m_day > rArg.m_day;
			}

			int m_day;
		};

		class year
		{
		public:

			//CONSTRUCTORS & STUFF

			constexpr explicit year(int year) noexcept
				: m_year(year)
			{
			}

			//METHODS & STUFF

			constexpr int get() const noexcept
			{
				return m_year;
			}

			constexpr year& operator++() noexcept
			{
				++m_year;
				return *this;
			}

			constexpr year operator++(int) noexcept
			{
				const year output{ *this };
				this->operator++();
				return output;
			}

			constexpr year& operator+=(year y) noexcept
			{
				m_year += y.get();
				return *this;
			}

			constexpr year& operator--() noexcept
			{
				--m_year;
				return *this;
			}

			constexpr year operator--(int) noexcept
			{
				const year output{ *this };
				this->operator--();
				return *this;
			}

			constexpr year& operator-=(year y) noexcept
			{
				m_year -= y.get();
				return *this;
			}

			void swap(year& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend constexpr year operator+(year lArg, year rArg) noexcept
			{
				return lArg += rArg;
			}

			friend constexpr year operator-(year lArg, year rArg) noexcept
			{
				return lArg -= rArg;
			}

			friend constexpr year operator-(year y) noexcept
			{
				return year(-y.m_year);
			}

			friend constexpr bool operator==(year lArg, year rArg) noexcept
			{
				return lArg.m_year == rArg.m_year;
			}

			friend constexpr bool operator!=(year lArg, year rArg) noexcept
			{
				return lArg.m_year != rArg.m_year;
			}

			friend constexpr bool operator<=(year lArg, year rArg) noexcept
			{
				return lArg.m_year <= rArg.m_year;
			}

			friend constexpr bool operator<(year lArg, year rArg) noexcept
			{
				return lArg.m_year < rArg.m_year;
			}

			friend constexpr bool operator>=(year lArg, year rArg) noexcept
			{
				return lArg.m_year >= rArg.m_year;
			}

			friend constexpr bool operator>(year lArg, year rArg) noexcept
			{
				return lArg.m_year > rArg.m_year;
			}

			int m_year;
		};

		class month_day
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit month_day(month m, day d)
				: m_month{m}, m_day{d}
				//have to do this b/c month and day do not have default constructors
			{
				VerifyDate(m, d);
			}

			//METHODS & STUFF

			constexpr month m() const noexcept
			{
				return m_month;
			}

			constexpr day d() const noexcept
			{
				return m_day;
			}

			void m(month m)
			{
				VerifyDate(m, m_day);
				m_month = m;
			}

			void d(day d)
			{
				VerifyDate(m_month, d);
				m_day = d;
			}

			month_day& operator+=(month) noexcept;
			month_day& operator-=(month) noexcept;
			month_day& operator+=(day) noexcept;
			month_day& operator-=(day) noexcept;

			void swap(month_day& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			inline static const int s_daysPerMonth[] = {
				31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
			};

			static void VerifyDate(month, day);

			friend bool operator==(month_day lArg, month_day rArg) noexcept
			{
				return (lArg.m_month == rArg.m_month) && (lArg.m_day == rArg.m_day);
			}

			friend bool operator!=(month_day lArg, month_day rArg) noexcept
			{
				return (lArg.m_month != rArg.m_month) || (lArg.m_day != rArg.m_day);
			}

			friend bool operator<(month_day lArg, month_day rArg) noexcept
			{
				return (lArg.m_month < rArg.m_month)
					|| ((lArg.m_month == rArg.m_month) && (lArg.m_day < rArg.m_day));
			}

			friend bool operator<=(month_day lArg, month_day rArg) noexcept
			{
				return (lArg < rArg) || (lArg == rArg);
			}

			friend bool operator>(month_day lArg, month_day rArg) noexcept
			{
				return (lArg.m_month > rArg.m_month)
					|| ((lArg.m_month == rArg.m_month) && (lArg.m_day > rArg.m_day));
			}

			friend bool operator>=(month_day lArg, month_day rArg) noexcept
			{
				return (lArg > rArg) || (lArg == rArg);
			}

			friend month_day operator+(month_day md, month m) noexcept
			{
				return md += m;
			}

			friend month_day operator+(month m, month_day md) noexcept
			{
				return md += m;
			}

			friend month_day operator-(month_day md, month m) noexcept
			{
				return md -= m;
			}

			friend month_day operator+(month_day md, day d) noexcept
			{
				return md += d;
			}

			friend month_day operator+(day d, month_day md) noexcept
			{
				return md += d;
			}

			friend month_day operator-(month_day md, day d) noexcept
			{
				return md -= d;
			}

			month m_month;
			day m_day;
		};

		month_day operator/(month, day);

		class month_day_year
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit month_day_year(month_day md, year y)
				: m_monthDay{ md }, m_year{ y }
				//have to do this b/c month_day and year do not have default constructors
			{
				VerifyDate(md, y);
			}

			//METHODS & STUFF

			constexpr month m() const noexcept
			{
				return m_monthDay.m();
			}

			constexpr day d() const noexcept
			{
				return m_monthDay.d();
			}

			constexpr year y() const noexcept
			{
				return m_year;
			}

			void m(month m)
			{
				m_monthDay.m(m);
				VerifyDate(m_monthDay, m_year);
			}

			void d(day d)
			{
				m_monthDay.d(d);
				VerifyDate(m_monthDay, m_year);
			}

			void y(year y)
			{
				VerifyDate(m_monthDay, y);
				m_year = y;
			}

			month_day_year& operator+=(day) noexcept;
			month_day_year& operator-=(day) noexcept;
			month_day_year& operator+=(month) noexcept;
			month_day_year& operator-=(month) noexcept;
			month_day_year& operator+=(year) noexcept;
			month_day_year& operator-=(year) noexcept;

			void swap(month_day_year& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			inline static const int s_daysPerMonth[] = {
				31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
			};

			static constexpr bool IsLeapYear(year y) noexcept
			{
				return ((y.get() % 100) != 0) ? ((y.get() % 4) == 0) : ((y.get() % 400) == 0);
			}

			static void VerifyDate(month_day, year);

			friend bool operator==(month_day_year lArg, month_day_year rArg) noexcept
			{
				return (lArg.m_monthDay == rArg.m_monthDay) && (lArg.m_year == rArg.m_year);
			}

			friend bool operator!=(month_day_year lArg, month_day_year rArg) noexcept
			{
				return (lArg.m_monthDay != rArg.m_monthDay) || (lArg.m_year != rArg.m_year);
			}

			friend bool operator<(month_day_year lArg, month_day_year rArg) noexcept
			{
				return (lArg.m_year < rArg.m_year)
					|| ((lArg.m_year == rArg.m_year) && (lArg.m_monthDay < rArg.m_monthDay));
			}

			friend bool operator>(month_day_year lArg, month_day_year rArg) noexcept
			{
				return (lArg.m_year > rArg.m_year)
					|| ((lArg.m_year == rArg.m_year) && (lArg.m_monthDay > rArg.m_monthDay));
			}

			friend bool operator<=(month_day_year lArg, month_day_year rArg) noexcept
			{
				return (lArg < rArg) || (lArg == rArg);
			}

			friend bool operator>=(month_day_year lArg, month_day_year rArg) noexcept
			{
				return (lArg > rArg) || (lArg == rArg);
			}

			friend month_day_year operator+(month_day_year md, month m) noexcept
			{
				return md += m;
			}

			friend month_day_year operator+(month m, month_day_year md) noexcept
			{
				return md += m;
			}

			friend month_day_year operator-(month_day_year md, month m) noexcept
			{
				return md -= m;
			}

			friend month_day_year operator+(month_day_year md, day d) noexcept
			{
				return md += d;
			}

			friend month_day_year operator+(day d, month_day_year md) noexcept
			{
				return md += d;
			}

			friend month_day_year operator-(month_day_year md, day d) noexcept
			{
				return md -= d;
			}

			friend month_day_year operator+(month_day_year md, year y) noexcept
			{
				return md += y;
			}

			friend month_day_year operator+(year y, month_day_year md) noexcept
			{
				return md += y;
			}

			friend month_day_year operator-(month_day_year md, year y) noexcept
			{
				return md -= y;
			}

			month_day m_monthDay;
			year m_year;
		};

		month_day_year operator/(month_day, year);

		class month_year
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit month_year(month m, year y)
				: m_month{ m }, m_year{ y }
			{
				VerifyDate(m, y);
			}

			//METHODS & STUFF

			constexpr month m() const noexcept
			{
				return m_month;
			}

			constexpr year y() const noexcept
			{
				return m_year;
			}

			void m(month m)
			{
				VerifyDate(m, m_year);
				m_month = m;
			}

			void y(year y)
			{
				VerifyDate(m_month, y);
				m_year = y;
			}

			month_year& operator+=(month) noexcept;
			month_year& operator-=(month) noexcept;

			month_year& operator+=(year y) noexcept
			{
				m_year += y;
				return *this;
			}

			month_year& operator-=(year y) noexcept
			{
				m_year -= y;
				return *this;
			}

			void swap(month_year& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			static void VerifyDate(month, year);

			friend bool operator==(month_year lArg, month_year rArg) noexcept
			{
				return (lArg.m_month == rArg.m_month) && (lArg.m_year == rArg.m_year);
			}

			friend bool operator!=(month_year lArg, month_year rArg) noexcept
			{
				return !(lArg == rArg);
			}

			friend bool operator<(month_year lArg, month_year rArg) noexcept
			{
				return (lArg.m_year < rArg.m_year)
					|| ((lArg.m_year == rArg.m_year) && (lArg.m_month < rArg.m_month));
			}

			friend bool operator>(month_year lArg, month_year rArg) noexcept
			{
				return (lArg.m_year > rArg.m_year)
					|| ((lArg.m_year == rArg.m_year) && (lArg.m_month > rArg.m_month));
			}

			friend bool operator<=(month_year lArg, month_year rArg) noexcept
			{
				return (lArg < rArg) || (lArg == rArg);
			}

			friend bool operator>=(month_year lArg, month_year rArg) noexcept
			{
				return (lArg > rArg) || (lArg == rArg);
			}

			friend month_year operator+(month_year my, month m) noexcept
			{
				return my += m;
			}

			friend month_year operator+(month m, month_year my) noexcept
			{
				return my += m;
			}

			friend month_year operator-(month_year my, month m) noexcept
			{
				return my -= m;
			}

			friend month_year operator+(month_year my, year y) noexcept
			{
				return my += y;
			}

			friend month_year operator+(year y, month_year my) noexcept
			{
				return my += y;
			}

			friend month_year operator-(month_year my, year y) noexcept
			{
				return my -= y;
			}

			month m_month;
			year m_year;
		};

		month_year operator/(month, year);

		//effectively a wrapper of month_day_year
		class month_year_day
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit month_year_day(month_year my, day d)
				: m_date{ month_day{my.m(), d}, my.y()}
			{
			}

			//METHODS & STUFF

			constexpr month m() const noexcept
			{
				return m_date.m();
			}

			constexpr year y() const noexcept
			{
				return m_date.y();
			}

			constexpr day d() const noexcept
			{
				return m_date.d();
			}

			void m(month m)
			{
				m_date.m(m);
			}

			void y(year y)
			{
				m_date.y(y);
			}

			void d(day d)
			{
				m_date.d(d);
			}

			month_year_day& operator+=(month m) noexcept
			{
				m_date += m;
				return *this;
			}

			month_year_day& operator-=(month m) noexcept
			{
				m_date -= m;
				return *this;
			}

			month_year_day& operator+=(year y) noexcept
			{
				m_date += y;
				return *this;
			}

			month_year_day& operator-=(year y) noexcept
			{
				m_date -= y;
				return *this;
			}

			month_year_day& operator+=(day d) noexcept
			{
				m_date += d;
				return *this;
			}

			month_year_day& operator-=(day d) noexcept
			{
				m_date -= d;
				return *this;
			}

			void swap(month_year_day& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend bool operator==(month_year_day lArg, month_year_day rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(month_year_day lArg, month_year_day rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(month_year_day lArg, month_year_day rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(month_year_day lArg, month_year_day rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(month_year_day lArg, month_year_day rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(month_year_day lArg, month_year_day rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend month_year_day operator+(month_year_day myd, month m) noexcept
			{
				return myd += m;
			}

			friend month_year_day operator+(month m, month_year_day myd) noexcept
			{
				return myd += m;
			}

			friend month_year_day operator-(month_year_day myd, month m) noexcept
			{
				return myd -= m;
			}

			friend month_year_day operator+(month_year_day myd, year y) noexcept
			{
				return myd += y;
			}

			friend month_year_day operator+(year y, month_year_day myd) noexcept
			{
				return myd += y;
			}

			friend month_year_day operator-(month_year_day myd, year y) noexcept
			{
				return myd -= y;
			}

			friend month_year_day operator+(month_year_day myd, day d) noexcept
			{
				return myd += d;
			}

			friend month_year_day operator+(day d, month_year_day myd) noexcept
			{
				return myd += d;
			}

			friend month_year_day operator-(month_year_day myd, day d) noexcept
			{
				return myd -= d;
			}

			month_day_year m_date;
		};

		month_year_day operator/(month_year, day);
		
		//effectively a wrapper of month_day
		class day_month
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit day_month(day d, month m)
				: m_date{ m, d }
			{
			}

			//METHODS & STUFF

			constexpr month m() const noexcept
			{
				return m_date.m();
			}

			constexpr day d() const noexcept
			{
				return m_date.d();
			}

			void m(month m)
			{
				m_date.m(m);
			}

			void d(day d)
			{
				m_date.d(d);
			}

			day_month& operator+=(day d) noexcept
			{
				m_date += d;
				return *this;
			}

			day_month& operator-=(day d) noexcept
			{
				m_date -= d;
				return *this;
			}

			day_month& operator+=(month m) noexcept
			{
				m_date += m;
				return *this;
			}

			day_month& operator-=(month m) noexcept
			{
				m_date -= m;
				return *this;
			}

			void swap(day_month& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend bool operator==(day_month lArg, day_month rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(day_month lArg, day_month rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(day_month lArg, day_month rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(day_month lArg, day_month rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(day_month lArg, day_month rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(day_month lArg, day_month rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend day_month operator+(day_month dm, day d) noexcept
			{
				return dm += d;
			}

			friend day_month operator+(day d, day_month dm) noexcept
			{
				return dm += d;
			}

			friend day_month operator-(day_month dm, day d) noexcept
			{
				return dm -= d;
			}

			friend day_month operator+(day_month dm, month m) noexcept
			{
				return dm += m;
			}

			friend day_month operator+(month m, day_month dm) noexcept
			{
				return dm += m;
			}

			friend day_month operator-(day_month dm, month m) noexcept
			{
				return dm -= m;
			}

			month_day m_date;
		};

		day_month operator/(day, month);

		//Effectively a wrapper for month_day_year
		class day_month_year
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit day_month_year(day_month dm, year y)
				: m_date{ month_day{dm.m(), dm.d()}, y }
			{
			}

			//METHODS & STUFF

			constexpr month m() const noexcept
			{
				return m_date.m();
			}

			constexpr year y() const noexcept
			{
				return m_date.y();
			}

			constexpr day d() const noexcept
			{
				return m_date.d();
			}

			void m(month m)
			{
				m_date.m(m);
			}

			void y(year y)
			{
				m_date.y(y);
			}

			void d(day d)
			{
				m_date.d(d);
			}

			day_month_year& operator+=(month m) noexcept
			{
				m_date += m;
				return *this;
			}

			day_month_year& operator-=(month m) noexcept
			{
				m_date -= m;
				return *this;
			}

			day_month_year& operator+=(year y) noexcept
			{
				m_date += y;
				return *this;
			}

			day_month_year& operator-=(year y) noexcept
			{
				m_date -= y;
				return *this;
			}

			day_month_year& operator+=(day d) noexcept
			{
				m_date += d;
				return *this;
			}

			day_month_year& operator-=(day d) noexcept
			{
				m_date -= d;
				return *this;
			}

			void swap(day_month_year& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend bool operator==(day_month_year lArg, day_month_year rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(day_month_year lArg, day_month_year rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(day_month_year lArg, day_month_year rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(day_month_year lArg, day_month_year rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(day_month_year lArg, day_month_year rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(day_month_year lArg, day_month_year rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend day_month_year operator+(day_month_year dmy, month m) noexcept
			{
				return dmy += m;
			}

			friend day_month_year operator+(month m, day_month_year dmy) noexcept
			{
				return dmy += m;
			}

			friend day_month_year operator-(day_month_year dmy, month m) noexcept
			{
				return dmy -= m;
			}

			friend day_month_year operator+(day_month_year dmy, year y) noexcept
			{
				return dmy += y;
			}

			friend day_month_year operator+(year y, day_month_year dmy) noexcept
			{
				return dmy += y;
			}

			friend day_month_year operator-(day_month_year dmy, year y) noexcept
			{
				return dmy -= y;
			}

			friend day_month_year operator+(day_month_year dmy, day d) noexcept
			{
				return dmy += d;
			}

			friend day_month_year operator+(day d, day_month_year dmy) noexcept
			{
				return dmy += d;
			}

			friend day_month_year operator-(day_month_year dmy, day d) noexcept
			{
				return dmy -= d;
			}

			month_day_year m_date;
		};

		day_month_year operator/(day_month, year);

		class day_year
		{
		public:

			//CONSTRUCTORS & STUFF

			constexpr explicit day_year(day d, year y)
				: m_day{ d }, m_year{ y }
			{
			}

			//METHODS & STUFF

			constexpr day d() const noexcept
			{
				return m_day;
			}

			constexpr year y() const noexcept
			{
				return m_year;
			}

			constexpr void d(day d)
			{
				m_day = d;
			}

			constexpr void y(year y)
			{
				m_year = y;
			}

			constexpr day_year& operator+=(day d) noexcept
			{
				m_day += d;
				return *this;
			}

			constexpr day_year& operator-=(day d) noexcept
			{
				m_day -= d;
				return *this;
			}

			constexpr day_year& operator+=(year y) noexcept
			{
				m_year += y;
				return *this;
			}

			constexpr day_year& operator-=(year y) noexcept
			{
				m_year -= y;
				return *this;
			}

			void swap(day_year& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend constexpr bool operator==(day_year lArg, day_year rArg) noexcept
			{
				return (lArg.m_year == rArg.m_year) && (lArg.m_day == rArg.m_day);
			}

			friend constexpr bool operator!=(day_year lArg, day_year rArg) noexcept
			{
				return (lArg.m_year != rArg.m_year) || (lArg.m_day != rArg.m_day);
			}

			friend constexpr bool operator<(day_year lArg, day_year rArg) noexcept
			{
				return (lArg.m_year < rArg.m_year)
					|| ((lArg.m_year == rArg.m_year) && (lArg.m_day < rArg.m_day));
			}

			friend constexpr bool operator<=(day_year lArg, day_year rArg) noexcept
			{
				return (lArg < rArg) || (lArg == rArg);
			}

			friend constexpr bool operator>(day_year lArg, day_year rArg) noexcept
			{
				return (lArg.m_year > rArg.m_year)
					|| ((lArg.m_year == rArg.m_year) && (lArg.m_day > rArg.m_day));
			}

			friend constexpr bool operator>=(day_year lArg, day_year rArg) noexcept
			{
				return (lArg > rArg) || (lArg == rArg);
			}

			friend constexpr day_year operator+(day_year dy, day d) noexcept
			{
				return dy += d;
			}

			friend constexpr day_year operator+(day d, day_year dy) noexcept
			{
				return dy += d;
			}

			friend constexpr day_year operator-(day_year dy, day d) noexcept
			{
				return dy -= d;
			}

			friend constexpr day_year operator+(day_year dy, year y) noexcept
			{
				return dy += y;
			}

			friend constexpr day_year operator+(year y, day_year dy) noexcept
			{
				return dy += y;
			}

			friend constexpr day_year operator-(day_year dy, year y) noexcept
			{
				return dy -= y;
			}

			day m_day;
			year m_year;
		};

		inline constexpr day_year operator/(day d, year y) noexcept
		{
			return day_year{ d, y };
		}

		//effectively a wrapper for month_day_year
		class day_year_month
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit day_year_month(day_year dy, month m)
				: m_date{ month_day{m, dy.d()}, dy.y() }
			{
			}

			//METHODS & STUFF

			constexpr day d() const noexcept
			{
				return m_date.d();
			}

			constexpr year y() const noexcept
			{
				return m_date.y();
			}

			constexpr month m() const noexcept
			{
				return m_date.m();
			}

			void d(day d)
			{
				m_date.d(d);
			}

			void y(year y)
			{
				m_date.y(y);
			}

			void m(month m)
			{
				m_date.m(m);
			}

			day_year_month& operator+=(day d) noexcept
			{
				m_date += d;
				return *this;
			}

			day_year_month& operator-=(day d) noexcept
			{
				m_date -= d;
				return *this;
			}

			day_year_month& operator+=(month m) noexcept
			{
				m_date += m;
				return *this;
			}

			day_year_month& operator-=(month m) noexcept
			{
				m_date -= m;
				return *this;
			}

			day_year_month& operator+=(year y) noexcept
			{
				m_date += y;
				return *this;
			}

			day_year_month& operator-=(year y) noexcept
			{
				m_date -= y;
				return *this;
			}

			void swap(day_year_month& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend bool operator==(day_year_month lArg, day_year_month rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(day_year_month lArg, day_year_month rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(day_year_month lArg, day_year_month rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(day_year_month lArg, day_year_month rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(day_year_month lArg, day_year_month rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(day_year_month lArg, day_year_month rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend day_year_month operator+(day_year_month dym, day d) noexcept
			{
				return dym += d;
			}

			friend day_year_month operator+(day d, day_year_month dym) noexcept
			{
				return dym += d;
			}

			friend day_year_month operator-(day_year_month dym, day d) noexcept
			{
				return dym -= d;
			}

			friend day_year_month operator+(day_year_month dym, month m) noexcept
			{
				return dym += m;
			}

			friend day_year_month operator+(month m, day_year_month dym) noexcept
			{
				return dym += m;
			}

			friend day_year_month operator-(day_year_month dym, month m) noexcept
			{
				return dym -= m;
			}

			friend day_year_month operator+(day_year_month dym, year y) noexcept
			{
				return dym += y;
			}

			friend day_year_month operator+(year y, day_year_month dym) noexcept
			{
				return dym += y;
			}

			friend day_year_month operator-(day_year_month dym, year y) noexcept
			{
				return dym -= y;
			}

			month_day_year m_date;
		};

		day_year_month operator/(day_year, month);

		//effectively a wrapper for month_year
		class year_month
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit year_month(year y, month m)
				: m_date{ m, y }
			{
			}

			//METHODS & STUFF

			constexpr month m() const noexcept
			{
				return m_date.m();
			}

			constexpr year y() const noexcept
			{
				return m_date.y();
			}

			void m(month m)
			{
				m_date.m(m);
			}

			void y(year y)
			{
				m_date.y(y);
			}

			year_month& operator+=(year y) noexcept
			{
				m_date += y;
				return *this;
			}

			year_month& operator-=(year y) noexcept
			{
				m_date -= y;
				return *this;
			}

			year_month& operator+=(month m) noexcept
			{
				m_date += m;
				return *this;
			}

			year_month& operator-=(month m) noexcept
			{
				m_date -= m;
				return *this;
			}

			void swap(year_month& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:
			
			friend bool operator==(year_month lArg, year_month rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(year_month lArg, year_month rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(year_month lArg, year_month rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(year_month lArg, year_month rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(year_month lArg, year_month rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(year_month lArg, year_month rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend year_month operator+(year_month ym, month m) noexcept
			{
				return ym += m;
			}

			friend year_month operator+(month m, year_month ym) noexcept
			{
				return ym += m;
			}

			friend year_month operator-(year_month ym, month m) noexcept
			{
				return ym -= m;
			}

			friend year_month operator+(year_month ym, year y) noexcept
			{
				return ym += y;
			}

			friend year_month operator+(year y, year_month ym) noexcept
			{
				return ym += y;
			}

			friend year_month operator-(year_month ym, year y) noexcept
			{
				return ym -= y;
			}

			month_year m_date;
		};

		year_month operator/(year, month);

		//effectively a wrapper for month_day_year
		class year_month_day
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit year_month_day(year_month ym, day d)
				: m_date{ month_day{ym.m(), d}, ym.y() }
			{
			}

			//METHODS & STUFF

			constexpr day d() const noexcept
			{
				return m_date.d();
			}

			constexpr year y() const noexcept
			{
				return m_date.y();
			}

			constexpr month m() const noexcept
			{
				return m_date.m();
			}

			void d(day d)
			{
				m_date.d(d);
			}

			void y(year y)
			{
				m_date.y(y);
			}

			void m(month m)
			{
				m_date.m(m);
			}

			year_month_day& operator+=(day d) noexcept
			{
				m_date += d;
				return *this;
			}

			year_month_day& operator-=(day d) noexcept
			{
				m_date -= d;
				return *this;
			}

			year_month_day& operator+=(month m) noexcept
			{
				m_date += m;
				return *this;
			}

			year_month_day& operator-=(month m) noexcept
			{
				m_date -= m;
				return *this;
			}

			year_month_day& operator+=(year y) noexcept
			{
				m_date += y;
				return *this;
			}

			year_month_day& operator-=(year y) noexcept
			{
				m_date -= y;
				return *this;
			}

			void swap(year_month_day& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend bool operator==(year_month_day lArg, year_month_day rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(year_month_day lArg, year_month_day rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(year_month_day lArg, year_month_day rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(year_month_day lArg, year_month_day rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(year_month_day lArg, year_month_day rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(year_month_day lArg, year_month_day rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend year_month_day operator+(year_month_day ymd, day d) noexcept
			{
				return ymd += d;
			}

			friend year_month_day operator+(day d, year_month_day ymd) noexcept
			{
				return ymd += d;
			}

			friend year_month_day operator-(year_month_day ymd, day d) noexcept
			{
				return ymd -= d;
			}

			friend year_month_day operator+(year_month_day ymd, month m) noexcept
			{
				return ymd += m;
			}

			friend year_month_day operator+(month m, year_month_day ymd) noexcept
			{
				return ymd += m;
			}

			friend year_month_day operator-(year_month_day ymd, month m) noexcept
			{
				return ymd -= m;
			}

			friend year_month_day operator+(year_month_day ymd, year y) noexcept
			{
				return ymd += y;
			}

			friend year_month_day operator+(year y, year_month_day ymd) noexcept
			{
				return ymd += y;
			}

			friend year_month_day operator-(year_month_day ymd, year y) noexcept
			{
				return ymd -= y;
			}

			month_day_year m_date;
		};

		year_month_day operator/(year_month, day);

		//add year_day here
		//effectively a wrapper for month_year
		class year_day
		{
		public:

			//CONSTRUCTORS & STUFF

			constexpr explicit year_day(year y, day d)
				: m_date{ d, y }
			{
			}

			//METHODS & STUFF

			constexpr year y() const noexcept
			{
				return m_date.y();
			}

			constexpr day d() const noexcept
			{
				return m_date.d();
			}

			constexpr void y(year y) noexcept
			{
				m_date.y(y);
			}

			constexpr void d(day d) noexcept
			{
				m_date.d(d);
			}

			year_day& operator+=(year y) noexcept
			{
				m_date += y;
				return *this;
			}

			year_day& operator-=(year y) noexcept
			{
				m_date -= y;
				return *this;
			}

			year_day& operator+=(day d) noexcept
			{
				m_date += d;
				return *this;
			}

			year_day& operator-=(day d) noexcept
			{
				m_date -= d;
				return *this;
			}

			void swap(year_day& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend bool operator==(year_day lArg, year_day rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(year_day lArg, year_day rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(year_day lArg, year_day rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(year_day lArg, year_day rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(year_day lArg, year_day rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(year_day lArg, year_day rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend year_day operator+(year_day yd, day d) noexcept
			{
				return yd += d;
			}

			friend year_day operator+(day d, year_day yd) noexcept
			{
				return yd += d;
			}

			friend year_day operator-(year_day yd, day d) noexcept
			{
				return yd -= d;
			}

			friend year_day operator+(year_day yd, year y) noexcept
			{
				return yd += y;
			}

			friend year_day operator+(year y, year_day yd) noexcept
			{
				return yd += y;
			}

			friend year_day operator-(year_day yd, year y) noexcept
			{
				return yd -= y;
			}

			day_year m_date;
		};

		inline constexpr year_day operator/(year y, day d) noexcept
		{
			return year_day{ y, d };
		}

		//effectively a wrapper for month_day_year
		class year_day_month
		{
		public:

			//CONSTRUCTORS & STUFF

			explicit year_day_month(year_day yd, month m)
				: m_date{ month_day{m, yd.d()}, yd.y() }
			{
			}

			//METHODS & STUFF

			constexpr day d() const noexcept
			{
				return m_date.d();
			}

			constexpr year y() const noexcept
			{
				return m_date.y();
			}

			constexpr month m() const noexcept
			{
				return m_date.m();
			}

			void d(day d)
			{
				m_date.d(d);
			}

			void y(year y)
			{
				m_date.y(y);
			}

			void m(month m)
			{
				m_date.m(m);
			}

			year_day_month& operator+=(day d) noexcept
			{
				m_date += d;
				return *this;
			}

			year_day_month& operator-=(day d) noexcept
			{
				m_date -= d;
				return *this;
			}

			year_day_month& operator+=(month m) noexcept
			{
				m_date += m;
				return *this;
			}

			year_day_month& operator-=(month m) noexcept
			{
				m_date -= m;
				return *this;
			}

			year_day_month& operator+=(year y) noexcept
			{
				m_date += y;
				return *this;
			}

			year_day_month& operator-=(year y) noexcept
			{
				m_date -= y;
				return *this;
			}

			void swap(year_day_month& other) noexcept
			{
				const auto temp = *this;
				*this = other;
				other = temp;
			}

		private:

			friend bool operator==(year_day_month lArg, year_day_month rArg) noexcept
			{
				return lArg.m_date == rArg.m_date;
			}

			friend bool operator!=(year_day_month lArg, year_day_month rArg) noexcept
			{
				return lArg.m_date != rArg.m_date;
			}

			friend bool operator<=(year_day_month lArg, year_day_month rArg) noexcept
			{
				return lArg.m_date <= rArg.m_date;
			}

			friend bool operator>=(year_day_month lArg, year_day_month rArg) noexcept
			{
				return lArg.m_date >= rArg.m_date;
			}

			friend bool operator<(year_day_month lArg, year_day_month rArg) noexcept
			{
				return lArg.m_date < rArg.m_date;
			}

			friend bool operator>(year_day_month lArg, year_day_month rArg) noexcept
			{
				return lArg.m_date > rArg.m_date;
			}

			friend year_day_month operator+(year_day_month ydm, day d) noexcept
			{
				return ydm += d;
			}

			friend year_day_month operator+(day d, year_day_month ydm) noexcept
			{
				return ydm += d;
			}

			friend year_day_month operator-(year_day_month ydm, day d) noexcept
			{
				return ydm -= d;
			}

			friend year_day_month operator+(year_day_month ydm, month m) noexcept
			{
				return ydm += m;
			}

			friend year_day_month operator+(month m, year_day_month ydm) noexcept
			{
				return ydm += m;
			}

			friend year_day_month operator-(year_day_month ydm, month m) noexcept
			{
				return ydm -= m;
			}

			friend year_day_month operator+(year_day_month ydm, year y) noexcept
			{
				return ydm += y;
			}

			friend year_day_month operator+(year y, year_day_month ydm) noexcept
			{
				return ydm += y;
			}

			friend year_day_month operator-(year_day_month ydm, year y) noexcept
			{
				return ydm -= y;
			}

			month_day_year m_date;
		};

		year_day_month operator/(year_day, month);
	}

	namespace chrono_literals
	{
		constexpr chrono::month operator"" _m(unsigned long long month) noexcept
		{
			return chrono::month(static_cast<int>(month));
		}

		constexpr chrono::day operator"" _d(unsigned long long day) noexcept
		{
			return chrono::day(static_cast<int>(day));
		}

		constexpr chrono::year operator"" _y(unsigned long long year) noexcept
		{
			return chrono::year(static_cast<int>(year));
		}
	}
}