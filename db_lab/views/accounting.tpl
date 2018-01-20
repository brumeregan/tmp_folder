% rebase('base.tpl')
<h1>Учет отправленных товаров</h1>
<!--TODO ADD post accounting data-->
<form action="POST">
    <select name="order">
        <option value="">DEf</option>
    </select>
    <select name="product_name">
        <option value=""></option>
    </select>
    <input type="number">
    <input type="date">
</form>

<table>
    <thead>
        <th>ID</th>
        <th>Order #</th>
        <th>Product</th>
        <th>Amount</th>
        <th>date</th>
    </thead>
    <tbody>
        %for item in items:
            <tr>
                <td>{{ item['id'] }}</td>
                <td>{{ item['order_code'] }}</td>
                <td>{{ item['product_name'] }}</td>
                <td>{{ item['amount_send'] }}</td>
                <td>{{ item['issued_date'] }}</td>
            </tr>
        %end
    </tbody>
</table>