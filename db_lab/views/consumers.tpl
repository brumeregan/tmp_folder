% rebase('base.tpl')
<h1>Потребители товаров</h1>
<table>
    <thead>
        <th>ID</th>
        <th>Company name</th>
        <th>Address</th>
        <th>Phone number</th>
        <th>Bank account</th>
    </thead>
    <tbody>
        %for item in items:
            <tr>
                <td>{{ item['id'] }}</td>
                <td>{{ item['company_name'] }}</td>
                <td>{{ item['address'] }}</td>
                <td>{{ item['phone_number'] }}</td>
                <td>{{ item['bank_account'] }}</td>
            </tr>
        %end
    </tbody>
</table>

