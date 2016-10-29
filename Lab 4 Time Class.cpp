#include <iostream>
#include <iomanip>

using namespace std;

class Time
{
public:
	int get_hour()
	{
		return hour;
	}
	int get_minutes()
	{
		return minutes;
	}
	double get_seconds()
	{
		return seconds;
	}
	Time(int h, int m, double s)
	{
		hour = h;
		minutes = m;
		seconds = s;
		s1 = static_cast<int>(seconds * 100);
		seconds = static_cast<double>(s1);
		seconds = seconds / 100;
	}
	Time(int h, int m)
	{
		hour = h;
		minutes = m;
	}
	Time(int h)
	{
		hour = h;
	}
	template <class T1, class T2>
	friend Time operator+(T1, T2);
private:
	int hour = 0;
	int minutes = 0;
	double seconds = 0;
	int s1 = 0;
};

class TimeSpan
{
public:
	TimeSpan(double s)
	{
		seconds_all = s;
		hour = static_cast<int> (seconds_all) / 3600;
		minutes = (static_cast<int> (seconds_all) % 3600) / 60;
		seconds = s - hour * 3600 - minutes * 60;
		s1 = static_cast<int>(seconds * 100);
		seconds = static_cast<double>(s1);
		seconds = seconds / 100;
	}
	double get_hour()
	{
		hour1 = static_cast<int>(seconds_all / 3600 * 100);
		hour2 = static_cast<double>(hour1);
		return (hour2 / 100);
	}
	double get_minutes()
	{
		minutes1 = static_cast<int>(seconds_all / 60 * 100);
		minutes2 = static_cast<double>(minutes1);
		return (minutes2 / 100);
	}
	double get_seconds()
	{
		seconds1 = static_cast<int>(seconds_all * 100);
		seconds2 = static_cast<double>(seconds1);
		return (seconds2 / 100);
	}
	friend ostream & operator<<(ostream &, TimeSpan);
	template <class T1, class T2>
	friend Time operator+(T1, T2);
private:
	double seconds = 0, seconds_all = 0;
	int hour = 0;
	int minutes = 0;
	int hour1 = 0;
	int minutes1 = 0;
	int seconds1 = 0;
	double hour2 = 0;
	double minutes2 = 0;
	double seconds2 = 0;
	int s1 = 0;
};

ostream & operator<<(ostream & o, Time t)
{
	o << "[" << t.get_hour() << ":" << t.get_minutes() << ":" << t.get_seconds() << "]";
	return o;
}

ostream & operator<<(ostream & o, TimeSpan t)
{
	o << "[" << t.hour << ":" << t.minutes << ":" << t.seconds << "]";
	return o;
}

template <class T1, class T2>

Time operator+(T1 t1, T2 t2)
{
	int m = 0, h = 0;
	double s = t1.seconds + t2.seconds;
	if (s >= 60)
	{
		s -= 60;
		m++;
	}
	m += t1.minutes + t2.minutes;
	if (m >= 60)
	{
		m -= 60;
		h++;
	}
	h += t1.hour + t2.hour;
	Time t(h, m, s);
	return t;
}

int main()
{
	Time t(13, 30);
	TimeSpan ts(1165.522);
	cout << "Output of Time: " << t << endl;
	cout << "Output of TimeSpan: " << ts << endl;
	cout << "Output of ts.get_minutes(): " << ts.get_minutes() << endl;
	cout << "Output of ts.get_seconds(): " << ts.get_seconds() << endl;
	cout << "Output for the sum of Time and TimeSpan: " << t + ts << endl;
	return 0;
}