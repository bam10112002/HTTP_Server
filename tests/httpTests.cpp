// #include <iostream>
// #include "../src/http/include/http.h"
// using std::cout;
// using std::endl;

// bool Methot(const std::string&, std::string);
// bool Path(const std::string&, std::string);
// bool Protocol(const std::string&, std::string);
// bool Accept(const std::string& request, HTTP::AcceptType);

// int main()
// {
//     // std::string req1 = "  GET /book HTTP/1.1\nAccept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8\n";
//     // std::string req2 = "POST /book/1    HTTP/1.1\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\n";
//     // std::string req3 = "GET    /about/my/some HTTP/1.1\nAccept: text/css,*/*;q=0.1\n";

//     // int count = 0;
//     // cout << "Parse Methot tests:" << endl;
//     // count += Methot(req1, "GET");
//     // count += Methot(req2, "POST");
//     // count += Methot(req3, "GET");
//     // cout << "Success: " << count << "\tFaled: " << 3-count << endl << endl;

//     // count = 0;
//     // cout << "Parse Path tests:" << endl;
//     // count += Path(req1, "/book");
//     // count += Path(req2, "/book/1");
//     // count += Path(req3, "/about/my/some");
//     // cout << "Success: " << count << "\tFaled: " << 3-count << endl << endl;

//     // count = 0;
//     // cout << "Parse Protocol tests:" << endl;
//     // count += Protocol(req1, "HTTP/1.1");
//     // count += Protocol(req2, "HTTP/1.1");
//     // count += Protocol(req3, "HTTP/1.1");
//     // cout << "Success: " << count << "\tFaled: " << 3-count << endl << endl;

//     return 0;
// }

// bool Methot(const std::string& request, std::string methot)
// {
//     HTTP http;
//     http.SetHttp(request);
//     return (http.Method() == methot);
// }
// bool Path(const std::string& request, std::string path)
// {
//     HTTP http;
//     http.SetHttp(request);
//     return (http.Path() == path);
// }
// bool Protocol(const std::string& request, std::string protocol)
// {
//     HTTP http;
//     http.SetHttp(request);
//     return (http.Protocol() == protocol);
// }

// bool Accept(const std::string& request, HTTP::AcceptType accept)
// {
//     HTTP http;
//     http.SetHttp(request);
//     return (http.Accept() == accept);
// }