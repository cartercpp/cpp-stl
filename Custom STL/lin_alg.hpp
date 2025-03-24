#pragma once

#include "exception.hpp"
#include "utility.hpp"
#include "contiguous_iterator.hpp"
#include "concepts.hpp"

namespace asv
{
	namespace lin_alg
	{
		//VECTOR STUFF HERE:

		template <typename numType>
		concept valid_vector_numtype = number<numType> && !is_const<numType> && !is_volatile<numType>
			&& !is_reference<numType>;

		template <typename numType, unsigned long long N> requires valid_vector_numtype<numType>
		class vector
		{
		public:

			static_assert(N > 0, "Cannot have a 0-dimensional vector.");

			using value_type = numType;
			using size_type = unsigned long long;
			using iterator = asv::forward_iterator<lin_alg::vector<numType, N>>;
			using const_iterator = asv::const_forward_iterator<lin_alg::vector<numType, N>>;
			using reverse_iterator = asv::reverse_iterator<lin_alg::vector<numType, N>>;
			using const_reverse_iterator = asv::const_reverse_iterator<lin_alg::vector<numType, N>>;

			//CONSTRUCTORS & STUFF

			constexpr vector() noexcept
			{
				for_each(begin(), end(), [](numType& value) -> void {
					value = 0;
				});
			}

			template <convertible_to<numType>... Ts>
			constexpr vector(Ts&&... args)
			{
				static_assert(sizeof...(args) <= N, "Excessive # of arguments given.");

				size_type index = 0;
				[[maybe_unused]] const char temp[] = {
					(this->operator[](index) = forward<Ts>(args), ++index, '0')...
				};

				while (index < N)
				{
					this->operator[](index) = 0;
					++index;
				}
			}

			//METHODS & STUFF

			static constexpr size_type size() noexcept
			{
				return N;
			}

			constexpr iterator begin() noexcept
			{
				return iterator{ &this->operator[](0) };
			}

			constexpr iterator end() noexcept
			{
				return iterator{ m_data + N + 1 };
			}

			constexpr const_iterator begin() const noexcept
			{
				return const_iterator{ &this->operator[](0) };
			}

			constexpr const_iterator end() const noexcept
			{
				return const_iterator{ m_data + N + 1 };
			}

			constexpr const_iterator cbegin() const noexcept
			{
				return const_iterator{ &this->operator[](0) };
			}

			constexpr const_iterator cend() const noexcept
			{
				return const_iterator{ m_data + N + 1 };
			}

			constexpr reverse_iterator rbegin() noexcept
			{
				return reverse_iterator{ &this->operator[](N - 1) };
			}

			constexpr reverse_iterator rend() noexcept
			{
				return reverse_iterator{ m_data };
			}

			constexpr const_reverse_iterator rbegin() const noexcept
			{
				return const_reverse_iterator{ &this->operator[](N - 1) };
			}

			constexpr const_reverse_iterator rend() const noexcept
			{
				return const_reverse_iterator{ m_data };
			}

			constexpr const_reverse_iterator crbegin() const noexcept
			{
				return const_reverse_iterator{ &this->operator[](N - 1) };
			}

			constexpr const_reverse_iterator crend() const noexcept
			{
				return const_reverse_iterator{ m_data };
			}

			const numType& operator[](size_type index) const
			{
				CheckBounds(index);

				return m_data[index + 1];
			}

			numType& operator[](size_type index)
			{
				CheckBounds(index);

				return m_data[index + 1];
			}

			constexpr vector<numType, N>& operator*=(numType scalar)
			{
				for_each(begin(), end(), [scalar](numType& value) -> void {
					value *= scalar;
				});

				return *this;
			}

			constexpr vector<numType, N>& operator/=(numType scalar)
			{
				for_each(begin(), end(), [scalar](numType& value) -> void {
					value /= scalar;
				});

				return *this;
			}

			constexpr vector<numType, N>& operator+=(const vector<numType, N>& other)
			{
				size_type index = 0;

				for_each(begin(), end(), [&index, &other](numType& value) -> void {
					value += other[index];
					++index;
				});

				return *this;
			}

			constexpr vector<numType, N>& operator-=(const vector<numType, N>& other)
			{
				size_type index = 0;

				for_each(begin(), end(), [&index, &other](numType& value) -> void {
					value -= other[index];
					++index;
				});

				return *this;
			}

		private:

			void CheckBounds(size_type index) const
			{
				if (index >= N)
					throw out_of_range{ "Out of bounds." };
			}

			numType m_data[N + 2];
		};
		
		template <typename numType, unsigned long long N> requires valid_vector_numtype<numType>
		constexpr vector<numType, N> operator*(vector<numType, N> vec, numType scalar)
		{
			return vec *= scalar;
		}

		template <typename numType, unsigned long long N> requires valid_vector_numtype<numType>
		constexpr vector<numType, N> operator*(numType scalar, vector<numType, N> vec)
		{
			return vec *= scalar;
		}

		template <typename numType, unsigned long long N> requires valid_vector_numtype<numType>
		constexpr vector<numType, N> operator/(vector<numType, N> vec, numType scalar)
		{
			return vec /= scalar;
		}

		template <typename numType, unsigned long long N> requires valid_vector_numtype<numType>
		constexpr vector<numType, N> operator+(vector<numType, N> lArg, const vector<numType, N>& rArg)
		{
			return lArg += rArg;
		}

		template <typename numType, unsigned long long N> requires valid_vector_numtype<numType>
		constexpr vector<numType, N> operator-(vector<numType, N> lArg, const vector<numType, N>& rArg)
		{
			return lArg -= rArg;
		}

		template <typename numType, unsigned long long N> requires valid_vector_numtype<numType>
		constexpr numType operator*(const vector<numType, N>& lArg, const vector<numType, N>& rArg)
		{
			numType output = 0;

			for (unsigned long long index = 0; index < N; ++index)
				output += lArg[index] * rArg[index];

			return output;
		}

		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------

		//MATRIX STUFF HERE:

		template <typename numType>
		concept valid_matrix_numtype = number<numType> && !unsigned_integral<numType>
			&& !is_const<numType> && !is_volatile<numType> && !is_reference<numType>;

		template <typename numType, unsigned long long rowCount, unsigned long long columnCount>
			requires valid_matrix_numtype<numType>
		class matrix
		{
		public:

			static_assert((rowCount > 0) && (columnCount > 0), "A matrix must be at least 1x1");

			using value_type = vector<numType, columnCount>;
			using size_type = unsigned long long;
			using iterator = asv::forward_iterator<matrix<numType, rowCount, columnCount>>;
			using const_iterator = asv::const_forward_iterator<matrix<numType, rowCount, columnCount>>;
			using reverse_iterator = asv::reverse_iterator<matrix<numType, rowCount, columnCount>>;
			using const_reverse_iterator
				= asv::const_reverse_iterator<matrix<numType, rowCount, columnCount>>;

			//CONSTRUCTORS & STUFF

			matrix() = default;

			template <convertible_to<value_type>... Ts>
			constexpr matrix(Ts&&... args)
			{
				static_assert(sizeof...(args) <= rowCount, "Excessive # of arguments given.");

				size_type index = 0;

				const char temp[] = {
					(this->operator[](index) = forward<Ts>(args), ++index, '\0')...
				};
			}

			//METHODS & STUFF

			static constexpr size_type rows() noexcept
			{
				return rowCount;
			}

			static constexpr size_type columns() noexcept
			{
				return columnCount;
			}

			static constexpr size_type elements() noexcept
			{
				return rowCount * columnCount;
			}

			constexpr iterator begin() noexcept
			{
				return iterator{ &this->operator[](0) };
			}

			constexpr iterator end() noexcept
			{
				return iterator{ m_data + rowCount + 1 };
			}

			constexpr const_iterator begin() const noexcept
			{
				return const_iterator{ &this->operator[](0) };
			}

			constexpr const_iterator end() const noexcept
			{
				return const_iterator{ m_data + rowCount + 1 };
			}

			constexpr const_iterator cbegin() const noexcept
			{
				return const_iterator{ &this->operator[](0) };
			}

			constexpr const_iterator cend() const noexcept
			{
				return const_iterator{ m_data + rowCount + 1 };
			}

			constexpr reverse_iterator rbegin() noexcept
			{
				return reverse_iterator{ &this->operator[](rowCount - 1) };
			}

			constexpr reverse_iterator rend() noexcept
			{
				return reverse_iterator{ m_data };
			}

			constexpr const_reverse_iterator rbegin() const noexcept
			{
				return const_reverse_iterator{ &this->operator[](rowCount - 1) };
			}

			constexpr const_reverse_iterator rend() const noexcept
			{
				return const_reverse_iterator{ m_data };
			}

			constexpr const_reverse_iterator crbegin() const noexcept
			{
				return const_reverse_iterator{ &this->operator[](rowCount - 1) };
			}

			constexpr const_reverse_iterator crend() const noexcept
			{
				return const_reverse_iterator{ m_data };
			}

			value_type& operator[](size_type index)
			{
				CheckBounds(index);

				return m_data[index + 1];
			}

			const value_type& operator[](size_type index) const
			{
				CheckBounds(index);

				return m_data[index + 1];
			}

			vector<numType, rowCount> column(size_type column) const
			{
				if (column >= columnCount)
					throw out_of_range{ "Out of bounds." };

				vector<numType, rowCount> output;

				for (size_type row = 0; row < rowCount; ++row)
					output[row] = this->operator[](row)[column];
													   //invokes lin_alg::vector's operator[]

				return output;
			}

			constexpr matrix<numType, rowCount, columnCount>& operator*=(numType scalar)
			{
				for_each(begin(), end(), [scalar](vector<numType, columnCount>& row) -> void {
					for_each(row.begin(), row.end(), [scalar](numType& value) -> void {
						value *= scalar; }
					);
				});

				return *this;
			}

			constexpr matrix<numType, rowCount, columnCount>& operator/=(numType scalar)
			{
				for_each(begin(), end(), [scalar](vector<numType, columnCount>& row) -> void {
					for_each(row.begin(), row.end(), [scalar](numType& value) -> void {
						value /= scalar; }
					);
				});

				return *this;
			}

			constexpr matrix<numType, columnCount, rowCount> transpose() const noexcept
			{
				matrix<numType, columnCount, rowCount> output;

				for (size_type row = 0; row < rowCount; ++row)
					for (size_type column = 0; column < columnCount; ++column)
						output[column][row] = this->operator[](row)[column];

				return output;
			}

			constexpr bool invertible() const requires (rowCount == columnCount)
			{
				return determinant() != 0;
			}

			constexpr numType determinant() const requires (rowCount == columnCount)
			{
				if constexpr (rowCount == 1)
					return this->operator[](0)[0];
				else if constexpr (rowCount == 2)
				{
					const numType a = this->operator[](0)[0],
						b = this->operator[](0)[1],
						c = this->operator[](1)[0],
						d = this->operator[](1)[1];

					return a * d - b * c;
				}
				else
				{
					numType output = 0;
					const size_type row = 0;
					
					for (size_type column = 0; column < columnCount; ++column)
					{
						const numType coefficient = this->operator[](row)[column];
						output += coefficient * cofactor(row, column);
					}

					return output;
				}
			}

			numType cofactor(size_type i, size_type j) const
			{
				if ((i >= rowCount) || (j >= columnCount))
					throw out_of_range{ "Out of bounds." };

				matrix<numType, rowCount - 1, columnCount - 1> smallerMatrix;
				
				for (size_type row = 0; row < i; ++row)
				{
					for (size_type column = 0; column < j; ++column)
						smallerMatrix[row][column] = this->operator[](row)[column];

					for (size_type column = j + 1; column < columnCount; ++column)
						smallerMatrix[row][column - 1] = this->operator[](row)[column];
				}

				for (size_type row = i + 1; row < rowCount; ++row)
				{
					for (size_type column = 0; column < j; ++column)
						smallerMatrix[row - 1][column] = this->operator[](row)[column];

					for (size_type column = j + 1; column < columnCount; ++column)
						smallerMatrix[row - 1][column - 1] = this->operator[](row)[column];
				}

				return (((i + j) % 2) == 0) ? smallerMatrix.determinant()
					: -smallerMatrix.determinant();
			}

			constexpr matrix<numType, rowCount, columnCount> cofactorMatrix() const
			{
				matrix<numType, rowCount, columnCount> output;

				for (size_type row = 0; row < rowCount; ++row)
					for (size_type column = 0; column < columnCount; ++column)
						output[row][column] = cofactor(row, column);

				return output;
			}

			constexpr matrix<numType, columnCount, rowCount> adjugate() const
			{
				if constexpr ((rowCount == 1) && (columnCount == 1))
					return *this;
				else if constexpr ((rowCount == 2) && (columnCount == 2))
				{
					const numType a = this->operator[](0)[0],
						b = this->operator[](0)[1],
						c = this->operator[](1)[0],
						d = this->operator[](1)[1];

					vector<numType, columnCount> row1{ d, -b },
						row2{ -c, a };

					return matrix<numType, 2, 2>{row1, row2};
				}
				else
					return cofactorMatrix().transpose();
			}

			matrix<numType, rowCount, columnCount> inverse() const;

		private:

			void CheckBounds(size_type index) const
			{
				if (index >= rowCount)
					throw out_of_range{ "Out of bounds." };
			}

			value_type m_data[rowCount + 2]; //vector<numType, columnCount> m_data[rowCount + 2]
		};

		template <typename numType, unsigned long long rows, unsigned long long columns>
			requires valid_matrix_numtype<numType>
		constexpr matrix<numType, rows, columns> operator*(matrix<numType, rows, columns> mat, numType scalar)
		{
			return mat *= scalar;
		}

		template <typename numType, unsigned long long rows, unsigned long long columns>
			requires valid_matrix_numtype<numType>
		constexpr matrix<numType, rows, columns> operator*(numType scalar, matrix<numType, rows, columns> mat)
		{
			return mat *= scalar;
		}

		template <typename numType, unsigned long long rows, unsigned long long columns>
			requires valid_matrix_numtype<numType>
		constexpr matrix<numType, rows, columns> operator/(matrix<numType, rows, columns> mat, numType scalar)
		{
			return mat /= scalar;
		}

		template <typename numType, unsigned long long ARows, unsigned long long AColumns,
			unsigned long long BRows, unsigned long long BColumns>
				requires valid_matrix_numtype<numType>
		constexpr matrix<numType, ARows, BColumns> operator*(const matrix<numType, ARows, AColumns>& lArg,
			const matrix<numType, BRows, BColumns>& rArg)
		{
			static_assert(AColumns == BRows, "In order to multiply matrices A and B, "
				"A's columns must = B's rows");

			matrix<numType, ARows, BColumns> output;
			for (unsigned long long row = 0; row < output.rows(); ++row)
				for (unsigned long long column = 0; column < output.columns(); ++column)
					output[row][column] = lArg[row] * rArg.column(column);

			return output;
		}

		template <typename numType, unsigned long long rowCount, unsigned long long columnCount>
			requires valid_matrix_numtype<numType>
		matrix<numType, rowCount, columnCount>
			matrix<numType, rowCount, columnCount>::inverse() const
		{
			if (!invertible())
				throw runtime_error{ "Matrix is not invertible." };

			return adjugate() / determinant();
		}
	}
}