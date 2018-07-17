#include <chrono>
#include "JTime.hpp"


const extern int32_t hashPrime;

const int NANO_BOUND = 1000000000;
const int NANOS_PER_SECOND = 1000000000;

Instant::Instant(int64_t seconds,int nano):seconds(seconds),nanos(nano){}

Instant Instant::fromEpochSecond(int64_t seconds){
    return Instant(seconds,0);
}
Instant Instant::fromEpochSecond(int64_t seconds,int nanoAdjustment){
    if(nanoAdjustment>=NANO_BOUND||nanoAdjustment<0){
        int modifier = nanoAdjustment/NANO_BOUND;
        seconds +=modifier;
        nanoAdjustment-=NANO_BOUND*modifier;
    }
    return Instant(seconds,nanoAdjustment);
}

Instant Instant::fromEpochMilisecond(int64_t miliseconds){
    int64_t seconds = miliseconds/1000;
    int nanos = (miliseconds%1000)*(NANOS_PER_SECOND/1000);
    return Instant(seconds,nanos);
}

Instant Instant::add(const Duration& dur)const{
    int64_t nSeconds = this->seconds+dur.getSeconds();
    int     nNanos = this->nanos+dur.getNanos();
    return Instant(nSeconds,nNanos);
}

Instant Instant::subtract(const Duration& dur)const{
    return add(-dur);
}

bool   Instant::isBefore(const Instant& i)const{
    if(this->seconds<i.seconds)
        return true;
    else if(this->seconds==i.seconds&&this->nanos<i.nanos)
        return true;
    else
        return false;
}

bool Instant::isAfter(const Instant& i)const{
    if(this->seconds>i.seconds)
        return true;
    else if(this->seconds==i.seconds&&this->nanos>i.nanos)
        return true;
    else
        return false;
}

int Instant::compareTo(const Instant& i)const{
    if(this->isAfter(i))
        return 1;
    else if(this->isBefore(i))
        return -1;
    else
        return 0;
}

bool Instant::operator==(const Instant& i)const{
    return this->compareTo(i)==0;
}

bool Instant::operator<(const Instant& i)const{
    return this->isBefore(i);
}

bool Instant::operator>(const Instant& i)const{
    return this->isAfter(i);
}

bool Instant::operator>=(const Instant& i)const{
    return (*this)==i||(*this)>i;
}

bool Instant::operator<=(const Instant& i)const{
    return (*this)==i||(*this)<i;
}

bool Instant::operator!=(const Instant& i)const{
    return (*this)<i||(*this)>i;
}

Instant Instant::operator+(const Duration& d)const{
    return this->add(d);
}
Instant Instant::operator-(const Duration& d)const{
    return this->subtract(d);
}

int64_t Instant::toEpochSecond()const{
    return this->seconds;
}

int Instant::getNanos()const{
    return this->nanos;
}

Instant Instant::truncateTo(ChronoUnit c)const{
    if(c==ChronoUnit::NANOSECONDS)
        return *this;
    else if(c==ChronoUnit::SECONDS){
        return Instant::fromEpochSecond(this->seconds);
    }else switch(c){
        case ChronoUnit::MICROSECONDS:
            return Instant::fromEpochSecond(this->seconds,(this->nanos/1000)*1000);
        break;
        case ChronoUnit::MILISECONDS:
            return Instant::fromEpochSecond(this->seconds,(this->nanos/1000000)*1000000);
        break;
        case ChronoUnit::MINUTES:
            return Instant::fromEpochSecond((this->seconds/60)*60);
        break;
        case ChronoUnit::HOURS:
            return Instant::fromEpochSecond((this->seconds/3600)*3600);
        break;
    }
}

int32_t Instant::hashCode()const{
    return hashcode(this->seconds)*hashPrime+hashcode(this->nanos);
};

int64_t Instant::get(ChronoUnit u)const{
    switch(u){
        case ChronoUnit::NANOSECONDS:
            return this->seconds*1000000000+this->nanos;
        break;
        case ChronoUnit::MICROSECONDS:
            return this->seconds*1000000+(this->nanos/1000);
        break;
        case ChronoUnit::MILISECONDS:
            return this->seconds*1000+(this->nanos/1000000);
        break;
        case ChronoUnit::SECONDS:
            return this->seconds;
        break;
        case ChronoUnit::MINUTES:
            return this->seconds/60;
        break;
        case ChronoUnit::HOURS:
            return this->seconds/3600;
        break;
    }
}

Duration::Duration(int64_t seconds,int nanos):seconds(seconds),nanos(nanos){}

Duration Duration::between(const Instant& i,const Instant& j){
    int64_t seconds = i.toEpochSecond()-j.toEpochSecond();
    int nanos = i.getNanos()-j.getNanos();
    while(nanos<0){
        seconds-=1;
        nanos+=1000000000;
    }
    return Duration(seconds,nanos);
}

Duration Duration::fromEpoch(const Instant& i){
    return Duration(i.toEpochSecond(),i.getNanos());
}

Duration Duration::ofSeconds(int64_t seconds,int nanoAdjustment){
    if(nanoAdjustment>=NANO_BOUND||nanoAdjustment<0){
        int modifier = nanoAdjustment/NANO_BOUND;
        seconds +=modifier;
        nanoAdjustment-=NANO_BOUND*modifier;
    }
    return Duration(seconds,nanoAdjustment);
}

Duration Duration::ofSeconds(int64_t seconds){
    return Duration(seconds,0);
}

Duration Duration::of(int64_t val,ChronoUnit u){
    int64_t seconds;
    int nanos;
    switch(u){
        case ChronoUnit::NANOSECONDS:
            seconds = val/NANOS_PER_SECOND;
            nanos = val%NANOS_PER_SECOND;
        break;
        case ChronoUnit::MICROSECONDS:
            seconds = val/(NANOS_PER_SECOND/1000);
            nanos = (val%(NANOS_PER_SECOND/1000))*1000;
        break;
        case ChronoUnit::MILISECONDS:
            seconds = val/1000;
            nanos = (val%1000)*1000000;
        break;
        case ChronoUnit::SECONDS:
            seconds = val;
            nanos = 0;
        break;
        case ChronoUnit::MINUTES:
            seconds = val*60;
            nanos = 0;
        break;
        case ChronoUnit::HOURS:
            seconds = val*3600;
            nanos = 0;
        break;
    }
    return Duration(seconds,nanos);
}

Duration Duration::negate()const{
	int64_t seconds = -this->seconds;
	int nanos = 1000000000-this->nanos;
	if(this->nanos!=0)
		seconds++;
	else
		nanos = 0;
	return Duration(seconds,nanos);
}

bool Duration::isNegative()const{
	return this->seconds<0;
}

Duration Duration::abs()const{
	if(isNegative())
		return negate();
	else
		return *this;
}

Duration Duration::operator -()const{
	return negate();
}

Duration Duration::add(const Duration& o)const{
	int64_t seconds = this->seconds+o.seconds;
	int nanos = this->nanos+o.nanos;
	return ofSeconds(seconds,nanos);
}

Duration Duration::subtract(const Duration& o)const{
	return add(-o);
}

Duration Duration::add(int64_t val,ChronoUnit u)const{
	return add(of(val,u));
}

Duration Duration::addSeconds(int64_t seconds)const{
	return add(ofSeconds(seconds));
}

Duration Duration::addMiliseconds(int64_t miliseconds)const{
	return add(of(miliseconds,ChronoUnit::MILISECONDS));
}

int Duration::getNanos()const{
	return this->nanos;
}

int64_t Duration::getSeconds()const{
	return this->seconds;
}

Duration Duration::truncateTo(ChronoUnit c)const{
	 if(c==ChronoUnit::NANOSECONDS)
	        return *this;
	else if(c==ChronoUnit::SECONDS){
		return ofSeconds(this->seconds);
	}else switch(c){
		case ChronoUnit::MICROSECONDS:
			return ofSeconds(this->seconds,(this->nanos/1000)*1000);
		break;
		case ChronoUnit::MILISECONDS:
			return ofSeconds(this->seconds,(this->nanos/1000000)*1000000);
		break;
		case ChronoUnit::MINUTES:
			return ofSeconds((this->seconds/60)*60);
		break;
		case ChronoUnit::HOURS:
			return ofSeconds((this->seconds/3600)*3600);
		break;
	}
	 throw "Error";
}

int Duration::compareTo(const Duration& o)const{
	if(this->seconds<o.seconds)
		return -1;
	else if(this->seconds>o.seconds)
		return 1;
	else if(this->nanos<o.nanos)
		return -1;
	else if(this->nanos>o.nanos)
		return 1;
	else
		return 0;
}

Duration Duration::operator-(const Duration& o)const{
	return subtract(o);
}

Duration Duration::operator+(const Duration& o)const{
	return add(o);
}

bool Duration::operator==(const Duration& o)const{
	return compareTo(o)==0;
}

bool Duration::operator<(const Duration& o)const{
	return compareTo(o)<0;
}

bool Duration::operator>(const Duration& o)const{
	return compareTo(o)>0;
}

bool Duration::operator<=(const Duration& o)const{
	return compareTo(o)<=0;
}

bool Duration::operator>=(const Duration& o)const{
	return compareTo(o)>=0;
}

bool Duration::operator!=(const Duration& o)const{
	return compareTo(o)!=0;
}

int32_t Duration::hashCode()const{
	return hashcode(this->seconds)*hashPrime+hashcode(this->nanos);
}


Instant Instant::now(){
	auto now = std::chrono::high_resolution_clock::now();
	auto epochTime = now.time_since_epoch();
	auto secondtime = std::chrono::duration_cast<std::chrono::seconds>(epochTime);
	auto nanotime = std::chrono::duration_cast<std::chrono::nanoseconds>(epochTime-secondtime);
	int64_t seconds = secondtime.count();
	int nanos= nanotime.count()%NANOS_PER_SECOND;
	return Instant(seconds,nanos);
}







