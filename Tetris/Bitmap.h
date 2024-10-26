#pragma once
#include <array>
#include<iostream>
#include<Windows.h>
struct Vector2i { int x, y; };

template<int N, int M> class Bitmap;

using Bitmap4x4 = Bitmap<4, 4>;

template<int width, int height>
class Bitmap
{
public:
	
	Bitmap();
	Bitmap(bool val);

	void SetAll(bool val);
	Bitmap<height, width> RotateClockwise()const;
	Bitmap<height, width> RotateCounterClockwise()const;

	template<int N0, int M0>
	Bitmap<width, height> Paste(Bitmap<N0,M0> stamp, int left, int top, int w = N0, int h = M0)const;
	template<int N0, int M0>
	Bitmap<width, height> PasteAndFilter(Bitmap<N0, M0> stamp, int left, int top)const;
	template<int N0, int M0>
	Bitmap<width, height> PasteOrFilter(Bitmap<N0, M0> stamp, int left, int top, int w = N0, int h = M0)const;
	template<int N0, int M0>
	bool Overlaps(Bitmap<N0, M0> stamp, int left, int top)const;

	std::array<bool, height>& operator[](size_t index);
	const std::array<bool, height>& operator[](size_t index) const;

	Bitmap<width, height> operator &(const Bitmap<width, height>& other) const;
	Bitmap<width, height> operator &&(const Bitmap<width, height>& other) const;

	Bitmap<width, height> operator |(const Bitmap<width, height>& other) const;
	Bitmap<width, height > operator ||(const Bitmap<width, height>& other) const;

	Bitmap<width, height> operator !() const;

	bool operator ==(const Bitmap<width, height>& other) const;
	bool operator !=(const Bitmap<width, height>& other) const;

	template<size_t N0, size_t M0>
	Bitmap<N0, M0> SubBitmap(size_t i, size_t j)const;

	size_t GetWidth() const;
	size_t GetHeight() const;

	static Bitmap<width, height> bFALSE();
	static Bitmap<width, height> bTRUE();

private:

	std::array<std::array<bool, height>, width> map;

};

template<int width, int height>
inline Bitmap<width, height>::Bitmap()
{

}

template<int width, int height>
inline Bitmap<width, height>::Bitmap(bool val)
{
	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			map[x][y] = val;
		}
	}

}

template<int width, int height>
inline void Bitmap<width, height>::SetAll(bool val)
{
	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y <height; y++) {
			map[x][y] = val;
		}
	}
}

template<int width, int height>
inline Bitmap<height, width> Bitmap<width, height>::RotateClockwise()const
{
	Bitmap<width, width> r();

	Vector2i vt;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			vt.x = -j;
			vt.y = i;

			r[vt.y][vt.x + height- 1] = map[j][i];

		}

	}
	return r;

}

template<int width, int height>
inline Bitmap<height, width> Bitmap<width, height>::RotateCounterClockwise()const
{
	Bitmap<width, height> r();

	Vector2i vt;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			vt.x = j;
			vt.y = -i;

			r[vt.y + width - 1][vt.x] = map[j][i];

		}

	}
	return r;
}

template<int width, int height>
template<int N0, int M0>
inline bool Bitmap<width, height>::Overlaps(Bitmap<N0, M0> stamp, int left, int top) const
{
	for (int j = 0; j < M0 && j + top < height; j++) {
		for (int i = 0; i < N0 && i + left < width; i++) {
			if(i + left >= 0 && (map[i + left][j + top] && stamp[i][j]) == true)
				return true;
		}
	}

	return false;
	Sleep(3000);
}

template<int width, int height>
template<size_t N0, size_t M0>
inline Bitmap<N0, M0> Bitmap<width, height>::SubBitmap(size_t i, size_t j) const
{
	Bitmap<N0, M0> r();

	for (unsigned x = 0; x < N0; x++) {
		for (unsigned y = 0; y < M0; y++) {
			r[x][y] = map[i + x][j + y];
		}
	}
	return r;
}

template<int width, int height>
inline std::array<bool, height>& Bitmap<width, height>::operator[](size_t index)
{
	return map[index];
}

template<int width, int height>
inline const std::array<bool, height>& Bitmap<width, height>::operator[](size_t index) const
{
	return map[index];
}

template<int width, int height>
inline Bitmap<width, height> Bitmap<width, height>::operator&(const Bitmap<width, height>& other) const
{
	Bitmap<width, height> r();

	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			r[y][x] = map[y][x] & other[y][x];
		}
	}

	return r;
}

template<int width, int height>
inline Bitmap<width, height> Bitmap<width, height>::operator&&(const Bitmap<width, height>& other) const
{
	Bitmap<width, height> r();

	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			r[y][x] = map[y][x] && other[y][x];
		}
	}

	return r;
}

template<int width, int height>
inline Bitmap<width, height> Bitmap<width, height>::operator|(const Bitmap<width, height>& other) const
{
	Bitmap<width, height> r();

	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			r[y][x] = map[y][x] | other[y][x];
		}
	}

	return r;
}

template<int width, int height>
inline Bitmap<width, height> Bitmap<width, height>::operator||(const Bitmap<width, height>& other) const
{
	Bitmap<width, height> r();

	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			r[y][x] = map[y][x] || other[y][x];
		}
	}

	return r;
}

template<int width, int height>
inline Bitmap<width, height> Bitmap<width, height>::operator!() const
{
	Bitmap<width, height> r;

	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			r[x][y] = !(map[x][y]);
		}
	}

	return r;
}

template<int width, int height>
inline bool Bitmap<width, height>::operator==(const Bitmap<width, height>& other) const
{
	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			if (map[x][y] != other[x][y])return false;
		}
	}
	return true;
}

template<int width, int height>
inline bool Bitmap<width, height>::operator!=(const Bitmap<width, height>& other) const
{
	return !(*this == other);
}

template<int width, int height>
inline size_t Bitmap<width, height>::GetWidth() const
{
	return width;
}

template<int width, int height>
inline size_t Bitmap<width, height>::GetHeight() const
{
	return width;
}

template<int width, int height>
inline Bitmap<width, height> Bitmap<width, height>::bFALSE()
{
	return Bitmap<width, height>(false);
}

template<int width, int height>
inline Bitmap<width, height> Bitmap<width, height>::bTRUE()
{
	return Bitmap<width, height>(true);
}


template<int width, int height>
template<int N0, int M0>
inline Bitmap<width, height> Bitmap<width, height>::Paste(Bitmap<N0, M0> stamp, int left, int top, int w, int h) const
{
	Bitmap<width, height> r = *this;

	for (unsigned x = 0; x < w; x++) {
		for (unsigned y = 0; y < h; y++) {
			if (x + left >= 0 && y + top >= 0 && x + left < width&& y + top < height)
				r[x + left][y + top] = stamp[x][y];
		}
	}

	return r;

}

template<int width, int height>
template<int N0, int M0>
inline Bitmap<width, height> Bitmap<width, height>::PasteAndFilter(Bitmap<N0, M0> stamp, int left, int top) const
{
	Bitmap<width, height> r = *this;

	for (unsigned x = 0; x < N0; x++) {
		for (unsigned y = 0; y < M0; y++) {
			if (x + left >= 0 && y + top >= 0 && x + left < width && y + top < height)
				r[x + left][y + top] = r[x + left][y + top] && stamp[x][y];
		}
	}

	return r;
}

template<int width, int height>
template<int N0, int M0>
inline Bitmap<width, height> Bitmap<width, height>::PasteOrFilter(Bitmap<N0, M0> stamp, int left, int top,int w, int h) const
{
	Bitmap<width, height> r = *this;

	for (unsigned x = 0; x < w; x++) {
		for (unsigned y = 0; y < h; y++) {
			if (x + left >= 0 && y + top >= 0 && x + left < width && y + top < height)
				r[x + left][y + top] = r[x + left][y + top] || stamp[x][y];
		}
	}

	return r;
}

