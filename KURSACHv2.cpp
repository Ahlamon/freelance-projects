#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void AddService();
void ViewServices();
void DeleteService();
void AddWorker();
void ViewWorkers();
void DeleteWorker();
void SumOrders();
void AddOrder();


#define BTN_ADD_SERVICE 101
#define BTN_VIEW_SERVICES 102
#define BTN_DELETE_SERVICE 103
#define BTN_ADD_WORKER 104
#define BTN_VIEW_WORKERS 105
#define BTN_DELETE_WORKER 106
#define BTN_SUM_ORDERS 107
#define BTN_ADD_ORDER 108
#define BTN_EXIT 109


struct Order {
    std::wstring customerName;
    std::wstring serviceName;
    std::wstring date; 
    std::wstring time; 
    double price;
};

std::vector<std::pair<std::wstring, double>> services; 
std::vector<std::wstring> workers;                     
std::vector<Order> orders;              

void InitializeData() {
    services.push_back({ L"Haircut", 150.0 });
    services.push_back({ L"Makeup", 250.0 });
    services.push_back({ L"Massage", 300.0 });
    services.push_back({ L"Manicure", 200.0 });
    services.push_back({ L"Pedicure", 250.0 });

    workers.push_back(L"Anna (Makeup)");
    workers.push_back(L"John (Haircut)");
    workers.push_back(L"Sarah (Massage)");
    workers.push_back(L"Emma (Manicure)");
    workers.push_back(L"Michael (Pedicure)");

    orders.push_back({ L"John Doe", L"Haircut", L"25.11.2024", L"10:00", 150.0 });
    orders.push_back({ L"Jane Smith", L"Makeup", L"25.11.2024", L"12:00", 250.0 });
    orders.push_back({ L"Emily Johnson", L"Massage", L"25.11.2024", L"14:00", 300.0 });
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    InitializeData();

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SalonApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        L"SalonApp", L"Salon Management System",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND btnAddService, btnViewServices, btnDeleteService;
    static HWND btnAddWorker, btnViewWorkers, btnDeleteWorker, btnSumOrders, btnAddOrder, btnExit;

    switch (msg) {
    case WM_CREATE:
        btnAddService = CreateWindow(L"BUTTON", L"Add Service", WS_VISIBLE | WS_CHILD,
            50, 50, 200, 40, hwnd, (HMENU)BTN_ADD_SERVICE, NULL, NULL);
        btnViewServices = CreateWindow(L"BUTTON", L"View Services", WS_VISIBLE | WS_CHILD,
            50, 110, 200, 40, hwnd, (HMENU)BTN_VIEW_SERVICES, NULL, NULL);
        btnDeleteService = CreateWindow(L"BUTTON", L"Delete Service", WS_VISIBLE | WS_CHILD,
            50, 170, 200, 40, hwnd, (HMENU)BTN_DELETE_SERVICE, NULL, NULL);
        btnAddWorker = CreateWindow(L"BUTTON", L"Add Worker", WS_VISIBLE | WS_CHILD,
            300, 50, 200, 40, hwnd, (HMENU)BTN_ADD_WORKER, NULL, NULL);
        btnViewWorkers = CreateWindow(L"BUTTON", L"View Workers", WS_VISIBLE | WS_CHILD,
            300, 110, 200, 40, hwnd, (HMENU)BTN_VIEW_WORKERS, NULL, NULL);
        btnDeleteWorker = CreateWindow(L"BUTTON", L"Delete Worker", WS_VISIBLE | WS_CHILD,
            300, 170, 200, 40, hwnd, (HMENU)BTN_DELETE_WORKER, NULL, NULL);
        btnSumOrders = CreateWindow(L"BUTTON", L"Sum Orders", WS_VISIBLE | WS_CHILD,
            50, 230, 200, 40, hwnd, (HMENU)BTN_SUM_ORDERS, NULL, NULL);
        btnAddOrder = CreateWindow(L"BUTTON", L"Add Order", WS_VISIBLE | WS_CHILD,
            300, 230, 200, 40, hwnd, (HMENU)BTN_ADD_ORDER, NULL, NULL);
        btnExit = CreateWindow(L"BUTTON", L"Exit", WS_VISIBLE | WS_CHILD,
            175, 290, 200, 40, hwnd, (HMENU)BTN_EXIT, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case BTN_ADD_SERVICE: AddService(); break;
        case BTN_VIEW_SERVICES: ViewServices(); break;
        case BTN_DELETE_SERVICE: DeleteService(); break;
        case BTN_ADD_WORKER: AddWorker(); break;
        case BTN_VIEW_WORKERS: ViewWorkers(); break;
        case BTN_DELETE_WORKER: DeleteWorker(); break;
        case BTN_SUM_ORDERS: SumOrders(); break;
        case BTN_ADD_ORDER: AddOrder(); break;
        case BTN_EXIT: PostQuitMessage(0); break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


void AddService() {
    HWND dialog = CreateWindowEx(0, L"STATIC", L"Add Service",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        400, 200, 300, 200, NULL, NULL, NULL, NULL);

    HWND hwndInputName = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        120, 20, 150, 20, dialog, NULL, NULL, NULL);
    CreateWindow(L"STATIC", L"Service Name:", WS_VISIBLE | WS_CHILD,
        20, 20, 100, 20, dialog, NULL, NULL, NULL);

    HWND hwndInputPrice = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        120, 60, 150, 20, dialog, NULL, NULL, NULL);
    CreateWindow(L"STATIC", L"Price (UAH):", WS_VISIBLE | WS_CHILD,
        20, 60, 100, 20, dialog, NULL, NULL, NULL);

    HWND btnOk = CreateWindow(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD,
        50, 120, 80, 30, dialog, (HMENU)1, NULL, NULL);
    HWND btnCancel = CreateWindow(L"BUTTON", L"Cancel", WS_VISIBLE | WS_CHILD,
        150, 120, 80, 30, dialog, (HMENU)2, NULL, NULL);

    ShowWindow(dialog, SW_SHOW);

    MSG msg;
    bool done = false;

    while (!done && GetMessage(&msg, NULL, 0, 0)) {
        if (msg.hwnd == btnOk && msg.message == WM_LBUTTONUP) {
            wchar_t name[100];
            wchar_t priceStr[20];
            GetWindowText(hwndInputName, name, 100);
            GetWindowText(hwndInputPrice, priceStr, 20);

            double price = _wtof(priceStr);
            services.push_back({ name, price });

            MessageBox(dialog, L"Service added successfully!", L"Info", MB_OK);
            done = true;
        }
        else if (msg.hwnd == btnCancel && msg.message == WM_LBUTTONUP) {
            MessageBox(dialog, L"Operation cancelled.", L"Info", MB_OK);
            done = true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(dialog);
}



void AddWorker() {
    HWND dialog = CreateWindowEx(0, L"STATIC", L"Add Worker",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        400, 200, 400, 200, NULL, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Worker Name:", WS_VISIBLE | WS_CHILD,
        20, 20, 100, 20, dialog, NULL, NULL, NULL);
    HWND hwndInputName = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        140, 20, 200, 20, dialog, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Service Name:", WS_VISIBLE | WS_CHILD,
        20, 60, 100, 20, dialog, NULL, NULL, NULL);
    HWND hwndInputService = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        140, 60, 200, 20, dialog, NULL, NULL, NULL);

    HWND btnOk = CreateWindow(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD,
        80, 120, 80, 30, dialog, (HMENU)1, NULL, NULL);
    HWND btnCancel = CreateWindow(L"BUTTON", L"Cancel", WS_VISIBLE | WS_CHILD,
        200, 120, 80, 30, dialog, (HMENU)2, NULL, NULL);

    ShowWindow(dialog, SW_SHOW);

    MSG msg;
    bool done = false;

    while (!done && GetMessage(&msg, NULL, 0, 0)) {
        if (msg.hwnd == btnOk && msg.message == WM_LBUTTONUP) {
            wchar_t name[100];
            wchar_t service[100];
            GetWindowText(hwndInputName, name, 100);
            GetWindowText(hwndInputService, service, 100);

            bool serviceExists = false;
            for (const auto& s : services) {
                if (s.first == service) {
                    serviceExists = true;
                    break;
                }
            }

            if (!serviceExists) {
                MessageBox(dialog, L"Service does not exist!", L"Error", MB_OK);
            }
            else {
                std::wstring worker = std::wstring(name) + L" (" + service + L")";
                workers.push_back(worker);

                MessageBox(dialog, L"Worker added successfully!", L"Info", MB_OK);
                done = true;
            }
        }
        else if (msg.hwnd == btnCancel && msg.message == WM_LBUTTONUP) {
            MessageBox(dialog, L"Operation cancelled.", L"Info", MB_OK);
            done = true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(dialog);
}


void ViewServices() {
    std::wstringstream ss;
    for (size_t i = 0; i < services.size(); ++i) {
        ss << i + 1 << L". " << services[i].first << L" - " << services[i].second << L" UAH\n";
    }

    if (services.empty()) {
        MessageBox(NULL, L"No services available!", L"Info", MB_OK);
    }
    else {
        MessageBox(NULL, ss.str().c_str(), L"List of Services", MB_OK);
    }
}


void DeleteService() {
    HWND dialog = CreateWindowEx(0, L"STATIC", L"Delete Service",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        400, 200, 300, 150, NULL, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Enter Service Number:", WS_VISIBLE | WS_CHILD,
        20, 20, 150, 20, dialog, NULL, NULL, NULL);

    HWND hwndInputIndex = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        180, 20, 50, 20, dialog, NULL, NULL, NULL);

    HWND btnOk = CreateWindow(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD,
        50, 70, 80, 30, dialog, (HMENU)1, NULL, NULL);
    HWND btnCancel = CreateWindow(L"BUTTON", L"Cancel", WS_VISIBLE | WS_CHILD,
        150, 70, 80, 30, dialog, (HMENU)2, NULL, NULL);

    ShowWindow(dialog, SW_SHOW);

    MSG msg;
    bool done = false;

    while (!done && GetMessage(&msg, NULL, 0, 0)) {
        if (msg.hwnd == btnOk && msg.message == WM_LBUTTONUP) {
            wchar_t indexStr[10];
            GetWindowText(hwndInputIndex, indexStr, 10);
            int index = _wtoi(indexStr) - 1;

            if (index >= 0 && index < services.size()) {
                services.erase(services.begin() + index);
                MessageBox(dialog, L"Service deleted successfully!", L"Info", MB_OK);
            }
            else {
                MessageBox(dialog, L"Invalid service number!", L"Error", MB_OK);
            }
            done = true;
        }
        else if (msg.hwnd == btnCancel && msg.message == WM_LBUTTONUP) {
            MessageBox(dialog, L"Operation cancelled.", L"Info", MB_OK);
            done = true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(dialog);
}




void AddOrder() {
    HWND dialog = CreateWindowEx(0, L"STATIC", L"Add Order",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        400, 200, 400, 300, NULL, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Customer Name:", WS_VISIBLE | WS_CHILD,
        20, 20, 100, 20, dialog, NULL, NULL, NULL);
    HWND hwndInputName = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        140, 20, 200, 20, dialog, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Service Name:", WS_VISIBLE | WS_CHILD,
        20, 60, 100, 20, dialog, NULL, NULL, NULL);
    HWND hwndInputService = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        140, 60, 200, 20, dialog, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Date (DD.MM.YYYY):", WS_VISIBLE | WS_CHILD,
        20, 100, 120, 20, dialog, NULL, NULL, NULL);
    HWND hwndInputDate = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        140, 100, 200, 20, dialog, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Time (HH:MM):", WS_VISIBLE | WS_CHILD,
        20, 140, 120, 20, dialog, NULL, NULL, NULL);
    HWND hwndInputTime = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        140, 140, 200, 20, dialog, NULL, NULL, NULL);

    HWND btnOk = CreateWindow(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD,
        80, 200, 80, 30, dialog, (HMENU)1, NULL, NULL);
    HWND btnCancel = CreateWindow(L"BUTTON", L"Cancel", WS_VISIBLE | WS_CHILD,
        200, 200, 80, 30, dialog, (HMENU)2, NULL, NULL);

    ShowWindow(dialog, SW_SHOW);


    MSG msg;
    bool done = false;

    while (!done && GetMessage(&msg, NULL, 0, 0)) {
        if (msg.hwnd == btnOk && msg.message == WM_LBUTTONUP) {
            wchar_t name[100], service[100], date[20], time[10];
            GetWindowText(hwndInputName, name, 100);
            GetWindowText(hwndInputService, service, 100);
            GetWindowText(hwndInputDate, date, 20);
            GetWindowText(hwndInputTime, time, 10);

            double price = 0.0;
            for (const auto& s : services) {
                if (s.first == service) {
                    price = s.second;
                    break;
                }
            }

            orders.push_back({ name, service, date, time, price });
            MessageBox(dialog, L"Order added successfully!", L"Info", MB_OK);
            done = true;
        }
        else if (msg.hwnd == btnCancel && msg.message == WM_LBUTTONUP) {
            MessageBox(dialog, L"Operation cancelled.", L"Info", MB_OK);
            done = true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(dialog);
}



void ViewWorkers() {
    std::wstringstream ss;
    for (size_t i = 0; i < workers.size(); ++i) {
        ss << i + 1 << L". " << workers[i] << L"\n";
    }
    MessageBox(NULL, ss.str().c_str(), L"List of Workers", MB_OK);
}

void DeleteWorker() {
    HWND dialog = CreateWindowEx(0, L"STATIC", L"Delete Worker",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        400, 200, 300, 150, NULL, NULL, NULL, NULL);

    CreateWindow(L"STATIC", L"Enter Worker Number:", WS_VISIBLE | WS_CHILD,
        20, 20, 150, 20, dialog, NULL, NULL, NULL);
    HWND hwndInputIndex = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        180, 20, 50, 20, dialog, NULL, NULL, NULL);

    HWND btnOk = CreateWindow(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD,
        50, 70, 80, 30, dialog, (HMENU)1, NULL, NULL);
    HWND btnCancel = CreateWindow(L"BUTTON", L"Cancel", WS_VISIBLE | WS_CHILD,
        150, 70, 80, 30, dialog, (HMENU)2, NULL, NULL);

    ShowWindow(dialog, SW_SHOW);

    MSG msg;
    bool done = false;

    while (!done && GetMessage(&msg, NULL, 0, 0)) {
        if (msg.hwnd == btnOk && msg.message == WM_LBUTTONUP) {
            wchar_t indexStr[10];
            GetWindowText(hwndInputIndex, indexStr, 10);
            int index = _wtoi(indexStr) - 1;

            if (index >= 0 && index < workers.size()) {
                workers.erase(workers.begin() + index);
                MessageBox(dialog, L"Worker deleted successfully!", L"Info", MB_OK);
            }
            else {
                MessageBox(dialog, L"Invalid worker number!", L"Error", MB_OK);
            }
            done = true;
        }
        else if (msg.hwnd == btnCancel && msg.message == WM_LBUTTONUP) {
            MessageBox(dialog, L"Operation cancelled.", L"Info", MB_OK);
            done = true;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(dialog);
}



void SumOrders() {
    double total = 0.0;

    for (const auto& order : orders) {
        total += order.price;
    }

    std::wstringstream ss;
    ss << L"Total revenue from orders: " << total << L" UAH";

    MessageBox(NULL, ss.str().c_str(), L"Revenue Summary", MB_OK);
}


