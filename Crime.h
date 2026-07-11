//
// Created by Austin Henneberg on 7/6/26.
//

#ifndef DSA_PROJECT2_CRIMESORTLA_CRIME_H
#define DSA_PROJECT2_CRIMESORTLA_CRIME_H

#include <vector>
using namespace std;
class Crime {
public:
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
    const vector<Record>& getRecords() {
        return this->records;
    }
    vector<pair<int,int>> getAreas() {
        vector<pair<int,int>> areas;
        int s = this->records.size();
        for (int i = 0; i < s; i++) {
            Crime::Record rcd  = this->records[i];
            pair<int,int> area = {rcd.recordID,rcd.areaID};
            areas.push_back(area);
        }
        return areas;
    }
    vector<pair<int,int>> getCrimes() {
        vector<pair<int,int>> crimes;
        int s = this->records.size();
        for (int i = 0; i < s; i++) {
            Crime::Record rcd  = this->records[i];
            pair<int,int> area = {rcd.recordID,rcd.crimeID};
            crimes.push_back(area);
        }
        return crimes;
    }
};

#endif //DSA_PROJECT2_CRIMESORTLA_CRIME_H
