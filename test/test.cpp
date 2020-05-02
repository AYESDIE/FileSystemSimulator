#include <fs.hpp>

int main()
{

    Disk *disk1 = new Disk();
    disk1->display();

    disk1->create('U', "F1");
    disk1->close();
    disk1->open('U', "F1");
    disk1->display();

    string essay = "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---100----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---200----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---300----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---400----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---500----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---600----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---700----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---800----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789---900----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789--1000----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789--1100----012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789--1200----";

    disk1->write(1300, essay);
    disk1->display();

    disk1->seek(-1, 0);
    disk1->display();

    disk1->read(1500);
    disk1->display();

    disk1->seek(-1, 0);
    disk1->display();

    disk1->write(13, "happybirthday");
    disk1->display();

    disk1->seek(0, -5);

    disk1->read(10);
    disk1->display();

    string sample = "try";
    sample = sample.substr(sample.find('y')+1);

    if (sample == "") {
        cout << "yes" << endl;
    }
    else
        cout << "no" << endl;


    // pointer test
    char test[3] = {'1','2','5'};
    char* pt;

    pt = &test[0];
    cout << "value: " << pt << endl;
    cout << "value: " << (pt+1) << endl;
    cout << "value: " << (pt+2) << endl;
    cout << "value: " << (pt+3) << endl;
    cout << "value: " << *(pt+3) << endl;
    if (*(pt+3) == ' ')
        cout << "nothing" << endl;
    else
        cout << "wtf" << endl;


    cout << "address: " << *(&test[1]) << " " << *(&test[1]+1) << endl;

    // open/close test
    disk1->close();
    disk1->open('I', "D1/D2/F4");
    disk1->create('U', "D1/D3/F5");
    disk1->display();

    // delete final test
    disk1->deleteNew("D1/D2");
    disk1->display();

    return 0;
}