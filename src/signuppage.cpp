#include "signuppage.h"
#include "scene1.h"
#include <QMessageBox>
#include "account.h"
#include "account_sidebar.h"
#include "centering.h"

/**
 * \brief signupPage constructor
 * \param parent, a pointer to the parent widget
 */
signupPage::signupPage(QWidget *parent) : QWidget(parent)
{
    //instantiates a jsonhandler instance
    json = new jsonhandler();

    //creates the form
    firstName = new QLabel("First Name*");
    lastName = new QLabel("Last Name*");
    username = new QLabel("Username*");
    pass = new QLabel("Password*");
    passConfirm = new QLabel("Confirm Password*");
    phone = new QLabel("Phone Number");
    dob = new QLabel("Date of Birth (MM/DD/YY)");
    gender = new QLabel("Gender");

    signup = new QPushButton("Sign Up");
    back = new QPushButton("Back");

    femaleRB = new QRadioButton("Female");
    maleRB = new QRadioButton("Male");
    otherRB = new QRadioButton("Other");

    code = new QComboBox();
    code->addItem("+1");
    code->addItem("+961");
    code->addItem("+20");
    code->addItem("+962");

    fntxt = new QLineEdit();
    lntxt = new QLineEdit();
    usernametxt = new QLineEdit();
    passtxt = new QLineEdit();
    passConftxt = new QLineEdit();
    passtxt-> setEchoMode(QLineEdit::Password);
    passConftxt-> setEchoMode(QLineEdit::Password);
    number = new QLineEdit();
    date = new QDateEdit();
    box = new QVBoxLayout();
    groupBox = new QGroupBox();
    profilePic = new QLabel();
    QPixmap bg (QPixmap(":/acctPic.jpeg").scaled(125,125));
    profilePic->setPixmap(bg);
    profilePic->setScaledContents(true);
    profilePic->setStyleSheet("border-radius: 25px");
    changepicBtn = new QPushButton("Upload photo");


    //sets the layout
    QGridLayout *Grid = new QGridLayout();
    setGridLayout(Grid);
    setGroupLayout(box, groupBox);
    setLayout(Grid);

    //styles the form
    setStyleSheet("QWidget{background-color: #fff}");

    //connects the QPushButtons
    QObject :: connect(back, SIGNAL(clicked()), this, SLOT(goBack()));
    QObject :: connect(signup, SIGNAL(clicked()), this, SLOT(onSubmit()));
    QObject :: connect(changepicBtn, SIGNAL(clicked()), this, SLOT(uploadPic()));
}

/**
* \brief Sets the widget of the grid layout
* \param *Grid, a pointer to a grid layout
*/
void signupPage ::  setGridLayout(QGridLayout *grid){

    grid->addWidget(firstName, 0, 0);
    grid->addWidget(lastName, 1, 0);

    grid->addWidget(profilePic, 1, 3);
    grid->addWidget(changepicBtn, 2, 3);

    grid->addWidget(username, 2, 0);
    grid->addWidget(pass, 3, 0);
    grid->addWidget(passConfirm, 4, 0);
    grid->addWidget(phone, 5, 0);

    grid->addWidget(signup, 8, 3);
    grid->addWidget(back, 8, 0);

    grid->addWidget(fntxt, 0, 1);
    grid->addWidget(lntxt, 1, 1);
    grid->addWidget(usernametxt, 2, 1);
    grid->addWidget(passtxt, 3, 1);
    grid->addWidget(passConftxt, 4, 1);
    grid->addWidget(code, 5, 1);
    grid->addWidget(number, 5, 2);

    grid->addWidget(dob, 6, 0);
    grid->addWidget(date, 6, 1);
    grid->addWidget(gender, 7, 0);
    grid->addWidget(groupBox, 7, 1);

}

/**
* \brief Sets the QRadioButtons in a VBoxLayout
* \param *box, a pointer to a vertical box layout
* \param *groupBox, a pointer to a group of buttons
*/
void signupPage :: setGroupLayout(QVBoxLayout *box, QGroupBox *groupBox){
    box->addWidget(maleRB);
    box->addWidget(femaleRB);
    box->addWidget(otherRB);
    groupBox->setLayout(box);
}

/**
* \brief Checks if the password passes the all necessary conditions.
* \param pass, password in string format
* \return bool, returns true if the password passes all the conditions. Returns false otherwise.
*/
bool signupPage :: checkPass(QString pass){
    int charnum = 0;
    int number = 0;
    int upper = 0;
    int lower = 0;

    for (const auto& character : pass){
        charnum++;
        if (character.isUpper()){
            upper++;
        }
        if(character.isLower()){
            lower++;
        }
        if(character.isDigit()){
            number++;
        }
    }

    if (charnum <8 || number <1 || upper < 1 || lower < 1){
        return false;
    }
    return true;
}

/**
* \brief Checks if any of the input fields are left empty.
* \return bool, returns true if all the fields are filled correctly. Returns false otherwise.
*/
bool signupPage :: notEmpty(){

    if (fntxt->text() == nullptr || lntxt->text() == nullptr
            || usernametxt->text() == nullptr || passtxt->text() == nullptr
            || passConftxt->text() == nullptr || picPath == nullptr
            || (!femaleRB->isChecked() && !maleRB->isChecked() && !otherRB->isChecked())){
        QMessageBox :: information(this, "Login Failed", "Missing required information.");
        return false;
    }
    return true;
}

/**
* \brief Allows the user to select a custom profile picture
*
* This function stores the local path to the selected profile picture in the user QJsonObject
*/
void signupPage :: uploadPic(){
    QString file_name = QFileDialog :: getOpenFileName(this, "Choose a picture", QDir :: homePath());
    QPixmap bg (QPixmap(file_name).scaled(125,125));
    profilePic->setPixmap(bg);
    profilePic->setScaledContents(true);
    profilePic->setStyleSheet("border-radius: 25px");
    picPath = new QString(file_name);
}

/**
* \brief Constructs a user QJsonObject and stores it in data.json
* \return QJsonObject, the constructed json object
*
* This function takes the inputs of the sign up form and checks whether they are valid.
* In case the inputs pass the validation checks, the function fills in a user json object with the corresponding inputs.
*/
QJsonObject signupPage :: storeinfo(){
    QString un = usernametxt->text(); //username
    QString fn = fntxt->text(); //first name
    QString ln = lntxt->text(); //last name
    QString pw = passtxt->text(); //password
    QString dob = date->text(); //date of birth
    code_nb = new QString(code->currentText() + "-" + number->text());
    QString pn = *code_nb; //phone number
    QString dp = *picPath; // display picture
    QString gender;

    if(maleRB->isChecked() == true){
        gender = "Male";
    }

    else if(femaleRB->isChecked() == true){
        gender = "Female";
    }
    else{
        gender = "Other";
    }

    QJsonObject settings1 {
        {"difficulty", 0},
        {"topic", 0},
        {"bg", 0}
    };

    QJsonObject settings2 {
        {"difficulty", 0},
        {"bg", 0},
    };

    QJsonObject game1 {
        {"settings", settings1},
        {"scores" , QJsonArray {}},
        {"highscore", 0}
    };

    QJsonObject game2 {
        {"settings", settings2},
        {"scores" , QJsonArray {}},
        {"highscore", 0},
        {"bonus", 0}
    };

    QJsonObject userobj {
        {"username" , un},
        {"password" , pw},
        {"first name" , fn},
        {"last name" , ln},
        {"date of birth", dob},
        {"phone number", pn},
        {"profile pic", dp},
        {"gender", gender},
        {"game1", game1},
        {"game2", game2}
     };

    //check if username exists
    for (auto v : json->userarr) {
        QJsonObject element = v.toObject();
        if (element.value("username").toString() == un){
            QMessageBox :: information(this, "Sign in Failed", "Username already exists");
            return{};
        }
    }

    //check if chosen password is valid
    if (!checkPass(pw)){
        QMessageBox :: information(this, "Sign in Failed", "Password should be at least 8 characters, and should contain 1 digit, 1 upper and 1 lower character");
        return {};
    } if (passtxt->text() != passConftxt->text()){
     QMessageBox :: information(this, "Confirmation Failed", "Passwords do not match.");
    }
        json->insertUser(userobj);
        return userobj;
    }

/**
* \brief Displays the Account widget in case the user json object is not empty
*/
void signupPage :: onSubmit(){

    QJsonObject jobj = storeinfo();
    if (notEmpty() && !jobj.isEmpty()){
        acc = new account(nullptr,jobj);
        hide();
        Centering::centerWidget(acc);
        acc->show();
        // navigate to next page
        return;

    }

}

/**
 * \brief returns to the previous window. In this case, it is Scene1.cpp
 */
void signupPage :: goBack(){
    hide();
    scene1 *intro = new scene1();
    Centering::centerWidget(intro);
    intro->show();
}

