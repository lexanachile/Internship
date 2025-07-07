#ifndef COMP_H
#define COMP_H

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QVector>
#include <QRegularExpression>


struct comp {
    QString section;
    int price;
    QString name;
    comp() : section(""), price(0), name("") {}
    friend QTextStream& operator<<(QTextStream& out, const comp& X) {
        out << X.name << " " << X.section << " " << X.price;
        return out;
    }
    friend QTextStream& operator>>(QTextStream& in, comp& X) {
        QString line = in.readLine();
        if (line.isEmpty()) return in;

        QRegularExpression regex(R"(^([\w\s]+)\s+(\w+)\s+(\d+)$)");;

        QRegularExpressionMatch match = regex.match(line);
        if (match.hasMatch()) {
            X.name = match.captured(1);
            X.section = match.captured(2);
            X.price = match.captured(3).toInt();
        }
        return in;
    }
    QString make_name() const {
        return name + " " + section + " " + QString::number(price);
    }
};

struct bag {
    int num;
    QString section;
    QString name;

    bag() : num(0), section(""), name("") {}

    friend QTextStream& operator<<(QTextStream& out, const bag& X) {
        out << X.name << " " << X.num << " " << X.section;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, bag& X) {
        QString line = in.readLine();
        if (line.isEmpty()) return in;

        QRegularExpression regex(R"(^([\w\s]+)\s+(\d+)\s+(\w+)$)");

        QRegularExpressionMatch match = regex.match(line);
        if (match.hasMatch()) {
            X.name = match.captured(1);
            X.num = match.captured(2).toInt();
            X.section = match.captured(3);
        }
        return in;
    }
    QString make_name() const {
        return name + " " + section + " " + QString::number(num);
    }
};

template <class T>
class COMP {
    QVector<T> M;
public:
    COMP() {}
    COMP(const COMP& X) {
        for (T a: X.M) {
            M.push_back(a);
        }
    }
    COMP& operator=(const COMP& X) {
        if (this != &X) {
            M.clear();
            for (T a: X.M) {
                M.push_back(a);
            }
        }
        return *this;
    }
    COMP& operator=(const QVector<T>& X) {
        M.clear();
        for (T a: X) {
            M.push_back(a);

        }
        return *this;
    }
    QVector<T> findItem(const QString& what) const {
        auto it = std::lower_bound(M.begin(), M.end(), what, [](const T& item, const QString& name) {
            return item.name < name;
        });
        QVector<T> temp;
        if (it != M.end() && it->name == what) {
            temp.push_back(*it);
        }
        return temp;
    }

    int GetCount() const{
        return M.size();
    }
    void reverse_sort() {
        std::sort(M.begin(), M.end(), [](const T&a, const T&b) {
            return a.name > b.name;
        });
    }
    int size () {
        return M.size();
    }
    T& at(int i) {
        return M[i];
    }
    void sect_sort() {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) {
            if (a.section == b.section) {
                return a.name > b.name;
            }
            return a.section < b.section;
        });
    }
    void sort() {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) {
            return a.name < b.name;
        });
    }
    friend QTextStream& operator<<(QTextStream& out, const COMP& X) {
        for (T a: X.M) {
            out << a << "\n";
        }
        return out;
    }
    friend QTextStream& operator>>(QTextStream& in, COMP& X) {
        while (!in.atEnd()) {
            T temp;
            in >> temp;
            X.M.push_back(temp);
        }
        std::sort(X.M.begin(), X.M.end(), [](const T& a, const T& b) {
            return a.name < b.name;
        });
        return in;
    }
    friend COMP operator+(const COMP& a, const COMP& b) {
        COMP<T> temp;

        temp.M = a.M;
        temp.M.append(b.M);


        std::sort(temp.M.begin(), temp.M.end(), [](const T& a, const T& b) {
            return a.name < b.name;
        });


        QVector<T> unique;
        for (int i = 0; i < temp.M.size(); ++i) {
            if (i == 0 || temp.M[i].name != temp.M[i - 1].name) {
                unique.push_back(temp.M[i]);
            }
        }


        temp.M = unique;

        return temp;
    }

};

#endif // COMP_H
