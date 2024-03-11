#pragma once
#include <chrono>
#include <condition_variable>
#include <functional>
#include <thread>
#include <windows.h>

class Countdown {

public:
	VOID SetTime(LONGLONG days, LONGLONG hours, LONGLONG minutes, LONGLONG seconds)
	{
		const auto total_hours = days * 24 + hours;
		remaining_time_ = _STD chrono::hours(total_hours) + _STD chrono::minutes(minutes) + _STD chrono::seconds(seconds);
	}

	_STD chrono::seconds GetRemainingTime() const {
		return remaining_time_;
	}

	LONGLONG GetDays() const {
		return _STD chrono::duration_cast<_STD chrono::hours>(this->remaining_time_).count() / 24;
	}

	LONGLONG GetHours() const {
		return _STD chrono::duration_cast<_STD chrono::hours>(this->remaining_time_).count() % 24;
	}

	LONGLONG GetMinutes() const {
		return _STD chrono::duration_cast<_STD chrono::minutes>(this->remaining_time_ % _STD chrono::hours(1)).count();
	}

	LONGLONG GetSeconds() const {
		return _STD chrono::duration_cast<_STD chrono::seconds>(this->remaining_time_ % _STD chrono::minutes(1)).count();
	}

	void StartTick(_STD function <void()> func = [] {}) {
		_STD thread([this, func] {
			while (remaining_time_.count() > 0) {
				_STD this_thread::sleep_for(_STD chrono::seconds(1));


				if (remaining_time_.count() > 0) {
					remaining_time_ -= _STD chrono::seconds(1);
				}
			}
				func();

			}).detach();
	}
	explicit Countdown() : remaining_time_(0) {}
private:
	_STD chrono::seconds remaining_time_;
};
