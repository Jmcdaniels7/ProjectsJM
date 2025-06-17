from django.shortcuts import render, redirect, get_object_or_404
from django.utils import timezone
from django.contrib.auth.models import User, auth
from django.contrib import messages
from django.contrib.auth.decorators import login_required  
from .models import Item
from .models import Order, PurchaseItem


# this is a view to what page opens when the website is first visited
def home(request):
    return render(request, 'store/home.html', {})

# This is for the home button on base.html to work
def homepage(request):
    return render(request, 'store/home.html', {})

def chatbot(request):
    return render(request, 'store/chatbot.html',{})

# Login view
def login(request):
    if request.method =='POST':
        username = request.POST['username']
        password = request.POST['password']

        user = auth.authenticate(username=username,password=password)

        if user is not None:
            auth.login(request, user)
            return redirect('/')
        else:
            messages.info(request, 'Invalid login, username or password is not registered')
            return redirect('login')
    else:
        return render(request, 'store/login.html')

# Logout view
def logout(request):
    auth.logout(request)
    return redirect('/')

# User registration view
def register(request):
    if request.method == 'POST':
        firstname = request.POST['firstname']
        lastname = request.POST['lastname']
        username = request.POST['username']
        email = request.POST['email']
        password = request.POST['password']
        confirmpassword = request.POST['confirmpassword']

        if password == confirmpassword:
            if User.objects.filter(email=email).exists():
                messages.info(request, 'Email is already in use.')
                return redirect('register')
            elif User.objects.filter(username=username).exists():
                messages.info(request, 'Username is already in use.')
                return redirect('register')
            else:
                user = User.objects.create_user(
                    first_name=firstname, last_name=lastname, email=email, password=password, username=username
                )
                user.save()
                messages.info(request, 'Account created successfully.')
                return redirect('login')
        else:
            messages.info(request, 'Passwords do not match.')
            return redirect('register')
    else:
        return render(request, 'store/register.html')

# Store page with optional search
def store_page(request):
    query = request.GET.get('q')
    if query:
        items = Item.objects.filter(title__icontains=query)
    else:
        items = Item.objects.all()
    return render(request, 'store/store_page.html', {'items': items})

def item_detail(request, id):
    item = get_object_or_404(Item, pk=id)
    return render(request, 'store/item_detail.html', {'item': item})

# Account Info Page 
@login_required
def account_info(request):
    user = request.user
    context = {
        'first_name': user.first_name,
        'last_name': user.last_name,
        'email': user.email,
        'username': user.username,
        'password': '********',  
    }
    return render(request, 'store/account_info.html', context)

@login_required
def current_orders(request):
    orders = Order.objects.filter(user=request.user).order_by('-order_date')
    return render(request, 'store/order.html', {'orders': orders})

@login_required
def order_history(request):
    return render(request, 'store/order_history.html')