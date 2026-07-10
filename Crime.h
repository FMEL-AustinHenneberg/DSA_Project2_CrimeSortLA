//
// Created by Austin Henneberg on 7/6/26.
//

#ifndef DSA_PROJECT2_CRIMESORTLA_CRIME_H
#define DSA_PROJECT2_CRIMESORTLA_CRIME_H

#endif //DSA_PROJECT2_CRIMESORTLA_CRIME_H
#include <vector>
using namespace std;
class Crime {
    struct Record {
        int recordID;
        int areaID;
        int crimeID;
        Record(int r, int a, int c) {
            this->recordID = r;
            this->areaID = a;
            this->crimeID = c;
        }
    };
private:
    vector<Record> records;
public:
    Crime() {};
    void insertRecord(int r, int a, int c) {
        Record rcd(r,a,c);
        records.push_back(rcd);
    };
    vector<Record> getRecords() {
        return this->records;
    }
};