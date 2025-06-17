from django.urls import path
from . import views

#please do not alter previous work

urlpatterns = [
    path('', views.home, name='home'),
    path('store/home/', views.homepage, name='homepage'),  # Fixed name here --do not fix previous work
    path('store/register/', views.register, name='register'),
    path('store/login/', views.login, name='login'),
    path('store/logout/', views.logout, name='logout'),
    path('store/chatbot/', views.chatbot, name='chatbot'),
    path('store/store_page/', views.store_page, name='store_page'),  # for store page
    path('store/item_detail/<int:id>/', views.item_detail, name='item_detail'),  # for item detail page
    path('store/account_info/', views.account_info, name='account_info'),
    path('store/orders/', views.current_orders, name='current_orders'),
    path('store/order_history/', views.order_history, name='order_history'),  
]
